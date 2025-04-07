/*
 * FTP Serveur for Arduino Due and Ethernet shield (W5100) or WIZ820io (W5200)
 * Copyright (c) 2014 by Jean-Michel Gallego
 *
 * Use Streaming.h from Mial Hart
 *
 * Use SdFat.h from William Greiman
 *   with extension for long names (see http://forum.arduino.cc/index.php?topic=171663.0 )
 *
 * Use Ethernet library with somes modifications:
 *   modification for WIZ820io (see http://forum.arduino.cc/index.php?topic=139147.0
 *     and https://github.com/jbkim/W5200-Arduino-Ethernet-library )
 *   need to add the function EthernetClient EthernetServer::connected()
 *     (see http://forum.arduino.cc/index.php?topic=169165.15
 *      and http://forum.arduino.cc/index.php?topic=182354.0 )
 *     In EthernetServer.h add:
 *           EthernetClient connected();
 *     In EthernetServer.cpp add:
 *           EthernetClient EthernetServer::connected()
 *           {
 *             accept();
 *             for( int sock = 0; sock < MAX_SOCK_NUM; sock++ )
 *               if( EthernetClass::_server_port[sock] == _port )
 *               {
 *                 EthernetClient client(sock);
 *                 if( client.status() == SnSR::ESTABLISHED ||
 *                     client.status() == SnSR::CLOSE_WAIT )
 *                   return client;
 *               }
 *             return EthernetClient(MAX_SOCK_NUM);
 *           }
 *
 * Commands implemented:
 *   USER, PASS
 *   CDUP, CWD, QUIT
 *   MODE, STRU, TYPE
 *   PASV, PORT
 *   ABOR
 *   DELE
 *   LIST, MLSD, NLST
 *   NOOP, PWD
 *   RETR, STOR
 *   MKD,  RMD
 *   RNTO, RNFR
 *   FEAT, SIZE
 *   SITE SIZE
 *
 * Tested with those clients:
 *   under Windows:
 *     FTP Rush : ok
 *     Filezilla : problem with RETR and STOR
 *   under Ubuntu:
 *     gFTP : ok
 *   with a second Arduino and sketch of SurferTim at
 *     http://playground.arduino.cc/Code/FTP
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "FtpServer.h"

// Workaround for http://gcc.gnu.org/bugzilla/show_bug.cgi?id=34734
#undef PROGMEM
#define PROGMEM __attribute__((section(".progmem.data")))

EthernetServer ftpServer(FTP_CTRL_PORT);
EthernetServer dataServer(FTP_DATA_PORT_PASV);

SdList sdl;

void FtpServer::init()
{
    // Tells the ftp server to begin listening for incoming connection
    ftpServer.begin();
    dataServer.begin();
    iniVariables();
}

void FtpServer::iniVariables()
{
    // Default for data port
    dataPort = FTP_DATA_PORT_DFLT;

    // Default Data connection is Active
    dataPassiveConn = false;

    // Set the root directory
    strcpy(cwdName, "/");

    cwdRNFR[0] = 0;
    cmdStatus = 0;
    transferStatus = 0;
    millisTimeOut = (uint32_t)FTP_TIME_OUT * 60 * 1000;
}

void FtpServer::service()
{
    if (cmdStatus == 0)
    {
        if (client.connected())
        {
#ifdef FTP_DEBUG
            Serial << F("Closing client") << endln;
#endif
            client.stop();
        }
#ifdef FTP_DEBUG
        Serial << F("Ftp server waiting for connection on port ") << FTP_CTRL_PORT << endln;
#endif
        cmdStatus = 1;
    }
    else if (cmdStatus == 1)  // Ftp server idle
    {
        client = ftpServer.connected();
        if (client > 0)   // A client connected
        {
            clientConnected();
            millisEndConnection = millis() + 10 * 1000; // wait client id during 30 s.
            cmdStatus = 2;
        }
    }
    else
    {
        if (!client.connected())
        {
            disconnectClient();
            iniVariables();
        }
        else if (readChar() > 0)         // got response
        {
            if (cmdStatus == 2)            // Ftp server waiting for user registration
            {
                if (userIdentity())
                    cmdStatus = 3;
                else
                    cmdStatus = 0;
            }
            else if (cmdStatus == 3)       // Ftp server waiting for user registration
            {
                if (userPassword())
                {
                    cmdStatus = 4;
                    millisEndConnection = millis() + millisTimeOut;
                }
                else
                    cmdStatus = 0;
            }
            else if (cmdStatus == 4)       // Ftp server waiting for user command
            {
                if (!processCommand())
                    cmdStatus = 0;
                else
                    millisEndConnection = millis() + millisTimeOut;
            }
        }
    }

    if (transferStatus == 1)           // Retrieve data
    {
        if (!doRetrieve())
            transferStatus = 0;
    }
    else if (transferStatus == 2)      // Store data
    {
        if (!doStore())
            transferStatus = 0;
    }
    else if (cmdStatus > 1 && !((int32_t)(millisEndConnection - millis()) > 0))
    {
        client << "530 Timeout" << endln;
        cmdStatus = 0;
    }
}

void FtpServer::clientConnected()
{
#ifdef FTP_DEBUG
    Serial << F("Client connected!") << endln;
#endif
    client << "220--- Welcome to FTP for Arduino ---" << endln;
    client << "220---   By Jean-Michel Gallego   ---" << endln;
    client << "220 --   Version " << FTP_SERVER_VERSION << "   --" << endln;
    iCL = 0;
}

void FtpServer::disconnectClient()
{
#ifdef FTP_DEBUG
    Serial << F("Disconnecting client") << endln;
#endif
    client.stop();
}

bool FtpServer::userIdentity()
{
    if (strcmp(command, "USER") != 0)
        client << "500 Syntax error" << endln;
    else if (strcmp(parameters, FTP_USER) != 0)
        client << "530 " << endln;
    else
    {
        client << "331 OK. Password required" << endln;
        strcpy(cwdName, "/");
        return true;
    }
    disconnectClient();
    return false;
}

bool FtpServer::userPassword()
{
    if (strcmp(command, "PASS") != 0)
        client << "500 Syntax error" << endln;
    else if (strcmp(parameters, FTP_PASS) != 0)
        client << "530 " << endln;
    else
    {
#ifdef FTP_DEBUG
        Serial << F("OK. Waiting for commands.") << endln;
#endif
        client << "230 OK." << endln;
        return true;
    }
    disconnectClient();
    return false;
}

void FtpServer::SendDateTimeFormatted(EthernetClient& client, uint16_t date, uint16_t time)
{
    client <<
        (int)FAT_YEAR(date) <<
        ((int)FAT_MONTH(date) < 10 ? "0" : "") << (int)FAT_MONTH(date) <<
        ((int)FAT_DAY(date) < 10 ? "0" : "") << (int)FAT_DAY(date) <<
        ((int)FAT_HOUR(time) < 10 ? "0" : "") << (int)FAT_HOUR(time) <<
        ((int)FAT_MINUTE(time) < 10 ? "0" : "") << (int)FAT_MINUTE(time) <<
        ((int)FAT_SECOND(time) < 10 ? "0" : "") << (int)FAT_SECOND(time);
}

bool FtpServer::processCommand()
{
    ///////////////////////////////////////
    //                                   //
    //      ACCESS CONTROL COMMANDS      //
    //                                   //
    ///////////////////////////////////////

    //
    //  CDUP - Change to Parent Directory 
    //
    if (strcmp(command, "CDUP") == 0)
    {
        char* pSep;
        bool ok = false;

        if (strlen(cwdName) > 1)
        {
            // if cwdName ends with '/', remove it
            if (cwdName[strlen(cwdName) - 1] == '/')
                cwdName[strlen(cwdName) - 1] = 0;
            // search last '/'
            pSep = strrchr(cwdName, '/');
            ok = pSep > cwdName;
            // if found, ends the string after its position
            if (ok)
            {
                *(pSep + 1) = 0;
                ok = sdl.chdir(cwdName);
            }
        }
        // if an error appends, move to root
        if (!ok)
        {
            strcpy(cwdName, "/");
            sdl.chdir(cwdName);
        }
        // Serial << cwdName << endln; // for debugging
        client << "200 Ok. Current directory is " << cwdName << endln;
    }
    //
    //  CWD - Change Working Directory
    //
    else if (strcmp(command, "CWD") == 0)
    {
        if (strcmp(parameters, ".") == 0)  // 'CWD .' is the same as PWD command
            client << "257 \"" << cwdName << "\" is your current directory" << endln;
        else
        {
            bool ok = true;
            char tmp[FTP_CWD_SIZE];
            if (strcmp(parameters, "/") == 0 || strlen(parameters) == 0)
                strcpy(cwdName, "/");            // go to root
            else
            {
                if (parameters[0] != '/') // relative path. Concatenate with current dir
                {
                    strcpy(tmp, cwdName);
                    if (tmp[strlen(tmp) - 1] != '/')
                        strcat(tmp, "/");
                    strcat(tmp, parameters);
                }
                else
                    strcpy(tmp, parameters);
                if (tmp[strlen(tmp) - 1] != '/')
                    strcat(tmp, "/");
                ok = sdl.chdir(tmp);   // try to change to new dir
                if (ok)
                {
                    strcpy(cwdName, tmp);
                    // Serial << cwdName << endln; // for debugging
                }
            }
            if (ok)
                client << "250 Ok. Current directory is " << cwdName << endln;
            else
                client << "550 Can't change directory to " << parameters << endln;
        }
    }
    //
    //  PWD - Print Directory
    //
    else if (strcmp(command, "PWD") == 0)
        client << "257 \"" << cwdName << "\" is your current directory" << endln;
    //
    //  QUIT
    //
    else if (strcmp(command, "QUIT") == 0)
    {
        client << "221 Goodbye" << endln;
        disconnectClient();
        return false;
    }

    ///////////////////////////////////////
    //                                   //
    //    TRANSFER PARAMETER COMMANDS    //
    //                                   //
    ///////////////////////////////////////

    //
    //  MODE - Transfer Mode 
    //
    else if (strcmp(command, "MODE") == 0)
    {
        if (strcmp(parameters, "S") == 0)
            client << "200 S Ok" << endln;
        // else if(strcmp(parameters, "B") == 0)
        //  client << "200 B Ok" << endln;
        else
            client << "504 Only S(tream) is suported" << endln;
    }
    //
    //  PASV - Passive Connection management
    //
    else if (strcmp(command, "PASV") == 0)
    {
        data.stop();
        dataServer.begin();
        dataIp = Ethernet.localIP();
        dataPort = FTP_DATA_PORT_PASV;
        //data.connect( dataIp, dataPort );
        //data = dataServer.available();
#ifdef FTP_DEBUG
        Serial << F("Connection management set to passive") << endln;
        Serial << F("Data port set to ") << dataPort << endln;
#endif
        client << "227 Entering Passive Mode ("
            << dataIp[0] << "," << dataIp[1] << "," << dataIp[2] << "," << dataIp[3]
            << "," << (dataPort >> 8) << "," << (dataPort & 255)
            << ")." << endln;
        dataPassiveConn = true;
    }
    //
    //  PORT - Data Port
    //
    else if (strcmp(command, "PORT") == 0)
    {
        data.stop();
        // get IP of data client
        dataIp[0] = atoi(parameters);
        char * p = strchr(parameters, ',');
        for (uint8_t i = 1; i < 4; i++)
        {
            dataIp[i] = atoi(++p);
            p = strchr(p, ',');
        }
        // get port of data client
        dataPort = 256 * atoi(++p);
        p = strchr(p, ',');
        dataPort += atoi(++p);
        if (p == NULL)
            client << "501 Can't interpret parameters" << endln;
        else
        {
#ifdef FTP_DEBUG
            Serial << F("Data IP set to ") << dataIp[0] << F(":") << dataIp[1]
                << F(":") << dataIp[2] << F(":") << dataIp[3] << endln;
            Serial << F("Data port set to ") << dataPort << endln;
#endif
            client << "200 PORT command successful" << endln;
            dataPassiveConn = false;
        }
    }
    //
    //  STRU - File Structure
    //
    else if (strcmp(command, "STRU") == 0)
    {
        if (strcmp(parameters, "F") == 0)
            client << "200 F Ok" << endln;
        // else if(strcmp(parameters, "R") == 0)
        //  client << "200 B Ok" << endln;
        else
            client << "504 Only F(ile) is suported" << endln;
    }
    //
    //  TYPE - Data Type
    //
    else if (strcmp(command, "TYPE") == 0)
    {
        if (strcmp(parameters, "A") == 0)
            client << "200 TYPE is now ASII" << endln;
        else if (strcmp(parameters, "I") == 0)
            client << "200 TYPE is now 8-bit binary" << endln;
        else
            client << "504 Unknow TYPE" << endln;
    }

    ///////////////////////////////////////
    //                                   //
    //        FTP SERVICE COMMANDS       //
    //                                   //
    ///////////////////////////////////////

    //
    //  ABOR - Abort
    //
    else if (strcmp(command, "ABOR") == 0)
    {
        if (transferStatus > 0)
        {
            file.close();
            data.stop();
            client << "426 Transfer aborted" << endln;
            transferStatus = 0;
        }
        client << "226 Data connection closed" << endln;
    }
    //
    //  DELE - Delete a File 
    //
    else if (strcmp(command, "DELE") == 0)
    {
        if (strlen(parameters) == 0)
            client << "501 No file name" << endln;
        else
        {
            char path[FTP_CWD_SIZE];
            char name[FTP_FIL_SIZE];
            makePathName(name, path, FTP_CWD_SIZE);
            // Serial << F("Deleting [") << name << F("] in [") << path << F("]") << endln;
            if (!sdl.chdir(path) || !sdl.exists(name))
                client << "550 File " << parameters << " not found" << endln;
            else
            {
                if (sdl.remove(name))
                    client << "250 Deleted " << parameters << endln;
                else
                    client << "450 Can't delete " << parameters << endln;
            }
        }
    }
    //
    //  LIST - List 
    //
    else if (strcmp(command, "LIST") == 0)
    {
        if (!dataConnect())
            client << "425 No data connection" << endln;
        else
        {
            client << "150 Accepted data connection" << endln;
            char fileName[FTP_FIL_SIZE];
            bool isFile;
            uint32_t fileSize;
            uint16_t createDate;
            uint16_t createTime;
            uint16_t lastWriteDate;
            uint16_t lastWriteTime;
            uint16_t nm = 0;
            //sdl.vwd()-> rewind();
            sdl.chdir(cwdName);
            while (sdl.nextFile(fileName, &isFile, &fileSize, &createDate, &createTime, &lastWriteDate, &lastWriteTime))
            {
                if (isFile)
                    data << "+r,s" << fileSize;
                else
                    data << "+/";
                data << ",\t" << fileName << endln;
                nm++;
            }
            client << "226 " << nm << " matches total" << endln;
            data.stop();
        }
    }
    //
    //  MLSD - Listing for Machine Processing (see RFC 3659)
    //
    else if (strcmp(command, "MLSD") == 0)
    {
        if (!dataConnect())
            client << "425 No data connection" << endln;
        else
        {
            client << "150 Accepted data connection" << endln;
            char fileName[FTP_FIL_SIZE];
            bool isFile;
            uint32_t fileSize;
            uint16_t createDate;
            uint16_t createTime;
            uint16_t lastWriteDate;
            uint16_t lastWriteTime;
            uint16_t nm = 0;
            sdl.chdir(cwdName);
            while (sdl.nextFile(fileName, &isFile, &fileSize, &createDate, &createTime, &lastWriteDate, &lastWriteTime))
            {
                //Serial << fileSize << endln;
                data << "Type=" << (isFile ? "file" : "dir") << ";";
                data << "Size=" << fileSize << ";";
                data << "Create=";
                SendDateTimeFormatted(data, createDate, createTime);
                data << ";" << "Modify=";
                SendDateTimeFormatted(data, lastWriteDate, lastWriteTime);
                data << "; " << fileName << endln;
                nm++;
            }
            client << "226-options: -a -l" << endln;
            client << "226 " << nm << " matches total" << endln;
            data.stop();
        }
    }
    //
    //  NLST - Name List 
    //
    else if (strcmp(command, "NLST") == 0)
    {
        if (!dataConnect())
            client << "425 No data connection" << endln;
        else
        {
            client << "150 Accepted data connection" << endln;
            char fileName[FTP_FIL_SIZE];
            bool isFile;
            uint32_t fileSize;
            uint16_t createDate;
            uint16_t createTime;
            uint16_t lastWriteDate;
            uint16_t lastWriteTime;
            uint16_t nm = 0;
            sdl.chdir(cwdName);
            while (sdl.nextFile(fileName, &isFile, &fileSize, &createDate, &createTime, &lastWriteDate, &lastWriteTime))
            {
                data << fileName << endln;
                nm++;
            }
            client << "226 " << nm << " matches total" << endln;
            data.stop();
        }
    }
    //
    //  NOOP
    //
    else if (strcmp(command, "NOOP") == 0)
    {
        // dataPort = 0;
        client << "200 Zzz..." << endln;
    }
    //
    //  RETR - Retrieve
    //
    else if (strcmp(command, "RETR") == 0)
    {
        if (strlen(parameters) == 0)
            client << "501 No file name" << endln;
        else
        {
            char path[FTP_CWD_SIZE];
            char name[FTP_FIL_SIZE];
            makePathName(name, path, FTP_CWD_SIZE);
            if (!sdl.chdir(path) || !sdl.exists(name))
                client << "550 File " << parameters << " not found" << endln;
            else
            {
                if (!sdl.openFile(&file, name, O_READ))
                    client << "450 Can't open " << parameters << endln;
                else
                {
                    if (!dataConnect())
                        client << "425 No data connection" << endln;
                    else
                    {
#ifdef FTP_DEBUG
                        Serial << F("Sending ") << parameters << endln;
#endif
                        client << "150-Connected to port " << dataPort << endln;
                        client << "150 " << file.fileSize() << " bytes to download" << endln;
                        millisBeginTrans = millis();
                        bytesTransfered = 0;
                        transferStatus = 1;
                    }
                }
            }
        }
    }
    //
    //  STOR - Store
    //
    else if (strcmp(command, "STOR") == 0)
    {
        if (strlen(parameters) == 0)
            client << "501 No file name" << endln;
        else
        {
            char path[FTP_CWD_SIZE];
            char name[FTP_FIL_SIZE];
            makePathName(name, path, FTP_CWD_SIZE);
            if (!sdl.chdir(path) || !sdl.openFile(&file, name, O_CREAT | O_TRUNC | O_RDWR))
                client << "451 Can't open/create " << parameters << endln;
            else if (!dataConnect())
            {
                client << "425 No data connection" << endln;
                file.close();
            }
            else
            {
#ifdef FTP_DEBUG
                Serial << F("Receiving ") << parameters << endln;
#endif
                client << "150 Connected to port " << dataPort << endln;
                millisBeginTrans = millis();
                bytesTransfered = 0;
                transferStatus = 2;
            }
        }
    }
    //
    //  MKD - Make Directory
    //
    else if (strcmp(command, "MKD") == 0)
    {
        if (strlen(parameters) == 0)
            client << "501 No directory name" << endln;
        else
        {
            char path[FTP_CWD_SIZE];
            char dir[FTP_FIL_SIZE];
            makePathName(dir, path, FTP_CWD_SIZE);
#ifdef FTP_DEBUG
            Serial << F("Creating directory ") << dir << F(" in ") << path << endln;
#endif
            bool ok = sdl.chdir(path);
            if (ok)
            {
                if (sdl.exists(dir))
                    client << "521 \"" << parameters << "\" directory already exists" << endln;
                else
                {
                    ok = sdl.mkdir(dir);
                    if (ok)
                        client << "257 \"" << parameters << "\" created" << endln;
                }
            }
            if (!ok)
            {
                client << "550 Can't create \"" << parameters << "\"" << endln;
            }
        }
    }
    //
    //  RMD - Remove a Directory 
    //
    else if (strcmp(command, "RMD") == 0)
    {
        if (strlen(parameters) == 0)
            client << "501 No directory name" << endln;
        else
        {
            char path[FTP_CWD_SIZE];
            char dir[FTP_FIL_SIZE];
            makePathName(dir, path, FTP_CWD_SIZE);
#ifdef FTP_DEBUG
            Serial << F("Deleting ") << dir << F(" in ") << path << endln;
#endif
            if (!sdl.chdir(path) || !sdl.exists(dir))
                client << "550 File " << parameters << " not found" << endln;
            else if (sdl.rmdir(dir))
                client << "250 \"" << parameters << "\" deleted" << endln;
            else
                client << "501 Can't delete \"" << parameters << "\"" << endln;
        }
    }
    //
    //  RNFR - Rename From 
    //
    else if (strcmp(command, "RNFR") == 0)
    {
        cwdRNFR[0] = 0;
        if (strlen(parameters) == 0)
            client << "501 No file name" << endln;
        else
        {
            char dir[FTP_FIL_SIZE];
            makePathName(dir, cwdRNFR, FTP_CWD_SIZE);
#ifdef FTP_DEBUG
            Serial << F("Renaming ") << dir << F(" in ") << cwdRNFR << endln;
#endif
            if (!sdl.chdir(cwdRNFR) || !sdl.exists(dir))
                client << "550 File " << parameters << " not found" << endln;
            else if (strlen(cwdRNFR) + strlen(dir) + 1 > FTP_CWD_SIZE)
                client << "500 Command line too long" << endln;
            else
            {
                if (cwdRNFR[strlen(cwdRNFR) - 1] != '/')
                    strcat(cwdRNFR, "/");
                strcat(cwdRNFR, dir);
                client << "350 RNFR accepted - file exists, ready for destination" << endln;
            }
        }
    }
    //
    //  RNTO - Rename To 
    //
    else if (strcmp(command, "RNTO") == 0)
    {
        if (strlen(cwdRNFR) == 0)
            client << "503 Need RNFR before RNTO" << endln;
        else if (strlen(parameters) == 0)
            client << "501 No file name" << endln;
        else
        {
            char path[FTP_CWD_SIZE];
            char dir[FTP_FIL_SIZE];
            makePathName(dir, path, FTP_CWD_SIZE);
            if (strlen(path) + strlen(dir) + 1 > FTP_CWD_SIZE)
                client << "500 Command line too long" << endln;
            else if (!sdl.chdir(path))
                client << "550 \"" << path << "\" is not directory" << endln;
            else
            {
                if (path[strlen(path) - 1] != '/')
                    strcat(path, "/");
                strcat(path, dir);
                if (sdl.exists(path))
                    client << "553 " << parameters << " already exists" << endln;
                else
                {
#ifdef FTP_DEBUG
                    Serial << F("Renaming ") << cwdRNFR << F(" to ") << path << endln;
#endif
                    if (sdl.rename(cwdRNFR, path))
                        client << "250 File successfully renamed or moved" << endln;
                    else
                        client << "451 Rename/move failure" << endln;
                }
            }
        }
    }

    ///////////////////////////////////////
    //                                   //
    //   EXTENSIONS COMMANDS (RFC 3659)  //
    //                                   //
    ///////////////////////////////////////

    //
    //  FEAT - New Features
    //
    else if (strcmp(command, "FEAT") == 0)
    {
        client << "211-Extensons suported:" << endln;
        client << " MLSD" << endln;
        client << " SIZE" << endln;
        client << " SITE FREE" << endln;
        client << " SITE NAME LONG" << endln;
        client << " SITE NAME 8.3" << endln;
        client << "211 End." << endln;
    }
    //
    //  SIZE - Size of the file
    //
    else if (strcmp(command, "SIZE") == 0)
    {
        if (strlen(parameters) == 0)
            client << "501 No file name" << endln;
        else
            /*
            // For testing l2sName()
            {
            char path[ FTP_CWD_SIZE ];
            char name[ FTP_FIL_SIZE ];
            char shortPathName[ FTP_CWD_SIZE ];
            makePathName( name, path, FTP_CWD_SIZE );
            if( path[ strlen( path ) - 1 ] != '/' )
            strcat( path, "/" );
            if( sdl.chdir( path ) && sdl.exists( name ) &&
            sdl.fullShortName( shortPathName, name, FTP_CWD_SIZE ) &&
            file.open( shortPathName, O_READ ) &&  file.isFile())
            {
            client << "213 " << file.fileSize() << endln;
            file.close();
            }
            else
            {
            file.close();
            client << "550 No such file " << parameters << endln;
            }
            }
            */
            // /*
            // The correct way
        {
            char path[FTP_CWD_SIZE];
            char name[FTP_FIL_SIZE];
            makePathName(name, path, FTP_CWD_SIZE);
            if (sdl.chdir(path) && sdl.openFile(&file, name, O_READ))
            {
                client << "213 " << file.fileSize() << endln;
                file.close();
            }
            else
                client << "550 No such file " << parameters << endln;
        }
        // */
    }
    //
    //  SITE - Sistem command
    //
    else if (strcmp(command, "SITE") == 0)
    {
        if (strcmp(parameters, "FREE") == 0)
        {
            client << "200 " << sdl.free() << " MB free of "
                << sdl.capacity() << " MB capacity" << endln;
        }
        /*
        else if(strcmp(parameters, "NAME LONG") == 0)
        {
        sdl.setNameLong(true);
        strcpy(cwdName, "/");
        client << "200 Ok. Use long names" << endln;
        cmdStatus = 0;
        }
        else if(strcmp(parameters, "NAME 8.3") == 0)
        {
        sdl.setNameLong( false );
        strcpy(cwdName, "/");
        client << "200 Ok. Use 8.3 names" << endln;
        cmdStatus = 0;
        }
        */
        else
            client << "500 Unknow SITE command " << parameters << endln;
    }
    //
    //  Unrecognized commands ...
    //
    else
        client << "500 Unknow command" << endln;

    return true;
}

int FtpServer::dataConnect()
{
    if (dataPassiveConn)
    {
        if (!data)
            data = dataServer.connected();
        return data;
    }
    else
        return data.connect(dataIp, dataPort);
}

bool FtpServer::doRetrieve()
{
    int16_t nb = file.read(buf, FTP_BUF_SIZE);
    if (nb > 0)
    {
        data.write(buf, nb);
        bytesTransfered += nb;
        return true;
    }
    closeTransfer();
    return false;
}

bool FtpServer::doStore()
{
    if (data.connected())
    {
        int16_t nb = data.read(buf, FTP_BUF_SIZE);
        if (nb > 0)
        {
            file.write(buf, nb);
            bytesTransfered += nb;
        }
        return true;
    }
    closeTransfer();
    return false;
}

void FtpServer::closeTransfer()
{
    uint32_t deltaT = (int32_t)(millis() - millisBeginTrans);
    if (deltaT > 0 && bytesTransfered > 0)
    {
        client << "226-File successfully transferred" << endln;
        client << "226 " << deltaT << " ms, "
            << bytesTransfered / deltaT << " kbytes/s" << endln;
    }
    else
        client << "226 File successfully transferred" << endln;

    file.close();
    data.stop();
}

// Read a char from client connected to ftp server
//
//  update cmdLine and command buffers, iCL and parameters pointers
//
//  return:
//    -2 if buffer cmdLine is full
//    -1 if line not completed
//     0 if empty line received
//    length of cmdLine (positive) if no empy line received 

int8_t FtpServer::readChar()
{
    int8_t rc = -1;

    if (client.available())
    {
        char c = client.read();
#ifdef FTP_DEBUG
        Serial << c;
#endif
        if (c == '\\')
        {
            c = '/';
        }

        if (c != '\r')
        {
            if (c != '\n')
            {
                if (iCL < FTP_CMD_SIZE)
                    cmdLine[iCL++] = c;
                else
                    rc = -2; //  Line too long
            }
            else
            {
                cmdLine[iCL] = 0;
                command[0] = 0;
                parameters = NULL;
                // empty line?
                if (iCL == 0)
                {
                    rc = 0;
                }
                else
                {
                    rc = iCL;
                    // search for space between command and parameters
                    char * pSpace = strchr(cmdLine, ' ');
                    if (pSpace != NULL)
                    {
                        if (pSpace - cmdLine > 4)
                            rc = -2; // Syntax error
                        else
                        {
                            strncpy(command, cmdLine, pSpace - cmdLine);
                            command[pSpace - cmdLine] = 0;
                            parameters = pSpace + 1;
                        }
                    }
                    else if (strlen(cmdLine) > 4)
                    {
                        rc = -2; // Syntax error.
                    }
                    else
                    {
                        strcpy(command, cmdLine);
                    }

                    iCL = 0;
                }
            }
        }
        if (rc > 0)
        {
            for (uint8_t i = 0; i < strlen(command); i++)
                command[i] = toupper(command[i]);
        }

        if (rc == -2)
        {
            iCL = 0;
            client << "500 Syntax error" << endln;
        }
    }
    return rc;
}

// Make path and name from cwdName and parameters
//
// 3 possible cases: parameters can be absolute path, relative path or only the name
//
// parameters:
//   name : where to store the name
//   path : where to store the path
//   maxpl : size of path' string
//
// return:
//    true, if convertion is done

bool FtpServer::makePathName(char* name, char* path, size_t maxpl)
{
    // If parameter has no '/', it is the name
    if (strchr(parameters, '/') == NULL)
    {
        if (strlen(cwdName) > maxpl)
            return false;
        strcpy(path, cwdName);
        strcpy(name, parameters);
    }
    else
    {
        // If parameter indicate a relative path, concatenate with current dir
        if (parameters[0] != '/')
        {
            if (strlen(cwdName) + strlen(parameters) + 1 > maxpl)
                return false;
            strcpy(path, cwdName);
            if (path[strlen(path) - 1] != '/')
                strcat(path, "/");
            strcat(path, parameters);
        }
        else
        {
            if (strlen(parameters) > maxpl)
                return false;
            strcpy(path, parameters);
        }
        // Extract name
        char * pName = strrchr(path, '/');
        if (strlen(pName) > FTP_FIL_SIZE)
            return false;
        strcpy(name, pName + 1);
        // Remove name from path
        *(pName + 1) = 0;
    }
    return true;
}


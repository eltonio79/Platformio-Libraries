#!/usr/bin/env bash

set -eu

cd "$(dirname "$0")/../.."

VERSION="$1"
DATE=$(date +%F)
TAG="v$VERSION"
VERSION_REGEX="[0-9a-z\\.\\-]+"

update_version_in_source () {
	IFS=".-" read MAJOR MINOR REVISION EXTRA < <(echo "$VERSION")
	UNDERLINE=$(printf -- '-%.0s' $(seq 1 ${#TAG}))

	sed -i~ -bE "s/version=$VERSION_REGEX/version=$VERSION/; s|ardu-badge.com/ArduinoJson/$VERSION_REGEX|ardu-badge.com/ArduinoJson/$VERSION|; " README.md
	rm README.md*~

	sed -i~ -bE "4s/HEAD/$TAG ($DATE)/; 5s/-+/$UNDERLINE/" CHANGELOG.md
	rm CHANGELOG.md*~

	sed -i~ -bE "s/\"version\":.*$/\"version\": \"$VERSION\",/" library.json
	rm library.json*~

	sed -i~ -bE "s/version=.*$/version=$VERSION/" library.properties
	rm library.properties*~

	sed -i~ -bE "s/version: .*$/version: $VERSION.{build}/" appveyor.yml
	rm appveyor.yml*~

	sed -i~ -bE \
		-e "s/ARDUINOJSON_VERSION .*$/ARDUINOJSON_VERSION \"$VERSION\"/" \
		-e "s/ARDUINOJSON_VERSION_MAJOR .*$/ARDUINOJSON_VERSION_MAJOR $MAJOR/" \
		-e "s/ARDUINOJSON_VERSION_MINOR .*$/ARDUINOJSON_VERSION_MINOR $MINOR/" \
		-e "s/ARDUINOJSON_VERSION_REVISION .*$/ARDUINOJSON_VERSION_REVISION $REVISION/" \
		src/ArduinoJson/version.hpp
	rm src/ArduinoJson/version.hpp*~
}

commit_new_version () {
	git add src/ArduinoJson/version.hpp README.md CHANGELOG.md library.json library.properties appveyor.yml
	git commit -m "Set version to $VERSION"
}

add_tag () {
	CHANGES=$(awk '/\* /{ FOUND=1; print; next } { if (FOUND) exit}' CHANGELOG.md)
	git tag -m "ArduinoJson $VERSION"$'\n'"$CHANGES" "$TAG"
}

push () {
	git push --follow-tags
}

update_version_in_source
commit_new_version
add_tag
push

extras/scripts/build-arduino-package.sh
extras/scripts/build-single-header.sh
extras/scripts/wandbox/publish.sh "../ArduinoJson-$TAG.h"

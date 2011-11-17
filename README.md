# C implementation of the Readability algorithm (plus some goodies)

## Dependencies:

- libxml2
- libpcre or ICU for regular expressions support


## Building:

- make

## Building with ICU rather than pcre:

- ICU=1 make

By default, both the readable program and the Python extension
will be built.

## Building for OS X using Xcode

- Create a new directory named readable
- Copy readable.h and readable.c in the newly created directory
- Copy the directory named unicode from the ICU headers into your project
(you can get it from the iPhoneSimulator SDK, under /usr/include/unicode)
- Add the readable parent directory, the unicode parent directory and
/usr/include/libxml2 to Header Search Path under Build Settings
- Add libicucore.dylib and libxml2.xylib to the Link Binary with libraries
Build Phase
- In your code, import readable.h

## Building for iOS using Xcode

- Create a new directory named readable
- Copy readable.h and readable.c in the newly created directory
- Add the readable parent directory and /usr/include/libxml2 to
Header Search Path under Build Settings
- Add libicucore.dylib and libxml2.xylib to the Link Binary with libraries
Build Phase
- In your code, import readable.h

## API:

### char * readable(const char *html, const char *url, const char *encoding, int options)


Parses HTML to extract the interesting contents.


- html: HTML code to parse
- url: URL where this HTML was fetched from
- encoding: HTML encoding
- options: See readable.h for the avaialble options

### char * next_page_url(const char *html, const char *url, const char *encoding);


Returns the url for the next page in a multipage article (pretty much in alpha):


- html: HTML code to parse
- url: URL where this HTML was fetched from
- encoding: HTML encoding

## License

This code is licensed under the AGPLv3. If you'd like to use the code under
a different license, drop me a line to alberto@garciahierro.com

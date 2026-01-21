//
// Created by mario on 10/1/26.
//

#include "../headers/controller.h"

#include <cstring>
#include <iosfwd>
#include <sstream>
#define MOD_GZIP_ZLIB_WINDOWSIZE 15
#define MOD_GZIP_ZLIB_CFACTOR    9
#define MOD_GZIP_ZLIB_BSIZE      8096

/** Compress a STL string using zlib with given compression level and return
  * the binary data. */
std::string compress_gzip(const std::string& str,int compressionlevel = Z_BEST_COMPRESSION)
{
    z_stream zs;                        // z_stream is zlib's control structure
    memset(&zs, 0, sizeof(zs));

    if (deflateInit2(&zs,
                     compressionlevel,
                     Z_DEFLATED,
                     MOD_GZIP_ZLIB_WINDOWSIZE + 16,
                     MOD_GZIP_ZLIB_CFACTOR,
                     Z_DEFAULT_STRATEGY) != Z_OK
    ) {
        throw(std::runtime_error("deflateInit2 failed while compressing."));
    }

    zs.next_in = (Bytef*)str.data();
    zs.avail_in = str.size();           // set the z_stream's input

    int ret;
    char outbuffer[32768];
    std::string outstring;

    // retrieve the compressed bytes blockwise
    do {
        zs.next_out = reinterpret_cast<Bytef*>(outbuffer);
        zs.avail_out = sizeof(outbuffer);

        ret = deflate(&zs, Z_FINISH);

        if (outstring.size() < zs.total_out) {
            // append the block to the output string
            outstring.append(outbuffer,
                             zs.total_out - outstring.size());
        }
    } while (ret == Z_OK);

    deflateEnd(&zs);

    if (ret != Z_STREAM_END) {          // an error occurred that was not EOF
        std::ostringstream oss;
        oss << "Exception during zlib compression: (" << ret << ") " << zs.msg;
        throw(std::runtime_error(oss.str()));
    }
    return outstring;
}
/**
 *Transform object httpResponse to string
 *send later as a char* with the response of the server to the client
 */
std::stringstream stringifyResponse(const httpResponse& response) {
    std::stringstream responseString;
    //response head
    responseString << response.getVersion() << " "
    << response.getStatus() <<  " "
    << HttpStatus::reasonPhrase(response.getStatus()) << "\r\n";//optional
    //remaining headers
    responseString << "Server: " << response.getServer() << "\r\n";
    responseString << "Content-Type: " << response.getContentType() << "\r\n";
    responseString << "Content-Encoding: gzip\r\n";
    if (!response.getHeader("Content-Length").empty()) {
        responseString << "Content-Length: " << response.getHeader("Content-Length") << "\r\n";
    }
    //response body
    responseString << "\r\n";
    responseString << compress_gzip(response.getBody());
    return responseString;
}
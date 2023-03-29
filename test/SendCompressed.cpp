#include <iostream>
#include <sstream>
#include <vector>
#include "zlib.h"

std::vector<char> compressString(const std::string &str)
{
    uLong srcSize = str.size();
    uLong destSize = compressBound(srcSize);

    std::vector<char> destBuffer(destSize);
    int res = compress(reinterpret_cast<Bytef *>(&destBuffer[0]), &destSize,
                       reinterpret_cast<const Bytef *>(str.data()), srcSize);

    if (res != Z_OK)
    {
        std::cerr << "String compression failed (error code: " << res << ")" << std::endl;
        exit(1);
    }

    destBuffer.resize(destSize);
    return destBuffer;
}

std::string decompressString(const std::vector<char> &compressedData)
{
    uLong destSize = 0;

    int res = uncompress(NULL, &destSize,
                         reinterpret_cast<const Bytef *>(&compressedData[0]), compressedData.size());

    if (res != Z_BUF_ERROR)
    {
        std::cerr << "Get decompressed size failed (error code: " << res << ")" << std::endl;
        exit(1);
    }

    std::vector<char> destBuffer(destSize);
    res = uncompress(reinterpret_cast<Bytef *>(&destBuffer[0]), &destSize,
                     reinterpret_cast<const Bytef *>(&compressedData[0]), compressedData.size());

    if (res != Z_OK)
    {
        std::cerr << "String decompression failed (error code: " << res << ")" << std::endl;
        exit(1);
    }

    return std::string(destBuffer.begin(), destBuffer.end());
}

int main()
{
    std::string inputString = "This is the string which needs to be compressed. It can be any length.";
    std::cout << "Original string: " << inputString << std::endl;

    std::vector<char> compressedData = compressString(inputString);
    std::cout << "Compressed string size: " << compressedData.size() << std::endl;

    std::string decompressedString = decompressString(compressedData);
    std::cout << "Decompressed string: " << decompressedString << std::endl;

    return 0;
}
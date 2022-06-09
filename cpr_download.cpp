#include <iostream>
#include <fstream>
#include <cpr/cpr.h>
#include <boost/filesystem.hpp>

namespace fs = boost::filesystem;
using namespace std;

bool downloadFile(const std::string& url, const std::string& filename)
{
    static uint64_t s_totalSize = 0; 
    std::string tmp_filename = filename + ".tmp";
    std::ofstream of(tmp_filename, std::ios::binary | std::ios::app);
    auto pos = of.tellp();
    std::cout << "of.tellp: " << pos << std::endl;
    
    cpr::Url cpr_url{url};
    cpr::Session s;
    s.SetVerifySsl(cpr::VerifySsl{false});
    s.SetUrl(cpr_url);
    //s.SetHeader(cpr::Header{{"Accept-Encoding", "gzip"}});
    
    auto fileLength = s.GetDownloadFileLength();
    s.SetRange(cpr::Range{pos, fileLength - 1});

    cpr::Response response = s.Download(of);
    s_totalSize += response.downloaded_bytes;
    
    std::cout << "response.status_code: " << response.status_code 
          << ", response.downloaded_bytes: " << response.downloaded_bytes 
          << std::endl;
              
    if (s_totalSize >= fileLength)
    {
        s_totalSize = 0;
        rename(tmp_filename.c_str(), filename.c_str());
        return true;
    }

    return false;
}

int main()
{
    std::string url = "http://192.21.1.61:9001/download/test11.zip";
    boost::filesystem::path p(url);
    std::string filename = p.filename().c_str();
    bool success = false;
    while (!success)
    {
        success = downloadFile(url, filename);
    }
    std::cout << "done! " << std::endl;
    return 0;
}


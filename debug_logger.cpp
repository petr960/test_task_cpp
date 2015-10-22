#include "debug_logger.h"
#include <stdio.h>
#include <fstream>

using namespace std;

struct Data {
  Data(int num, std::wstring text) {
    this->num = num;
    this->text = text;
  }
  int num;
  std::wstring text;

};

namespace stxDebug {

template<>
struct GetDbgStringT<Data> {
  static std::wstring GetDbgString(const Data& data) 
  {
    wchar_t sbuf[12];
    std::wstring str = L"{ class: 'Data', object: { num: ";

    swprintf(sbuf, 12, L"%d", data.num);
    str += sbuf;
    str += L" , text: " + data.text + L" } }";
    
    return str;
  }
};

struct FileWriter
{
  void operator()(const std::wstring& msg) 
  {
    size_t dpos = msg.find(L'\n');
    std::wstring fname_w = msg.substr(0, dpos);
    std::string fname(fname_w.begin(), fname_w.end());

    wofstream ofs(fname.c_str(), ios_base::app);

    if (!ofs.bad()) {
       ofs << msg.substr(dpos + 1) << std::endl; 
    } 
  }
};

class DebugFileLogger : public DebugLogger<FileWriter>
{
public:
  DebugFileLogger(const std::wstring& fname) { *this << fname << L"\n"; }
};

stxDebug::DebugFileLogger File(const std::wstring& fname) {
  return DebugFileLogger(fname);
}

} // namespace stxDebug

int main(int argc, const char* argv[]) {
  cout << "stx C++ test task" << endl;

  stxDebug::Out() << L"wide text" << std::wstring(L" - std::wstring") << " - ascii text" << std::string(" - std::string");
  stxDebug::Err() << L"wide text" << std::wstring(L" - std::wstring") << " - ascii text" << std::string(" - std::string");

  // stx: task is to uncomment and revive this line
  // stxDebug::File(L"dump.txt") << L"Dump of data: " << Data(55, "stx data");

  stxDebug::File(L"dump.txt") << L"Dump of data: " << Data(55, L"stx data");

  return 0;
}

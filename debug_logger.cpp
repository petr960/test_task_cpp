#include "debug_logger.h"

using namespace std;

namespace stxDebug {

} // namespace stxDebug

struct Data {
  Data(int num, std::wstring text) {
    this->num = num;
    this->text = text;
  }
  int num;
  std::wstring text;
};

int main(int argc, const char* argv[]) {
  cout << "stx C++ test task" << endl;

  stxDebug::Out() << L"wide text" << std::wstring(L" - std::wstring") << " - ascii text" << std::string(" - std::string");
  stxDebug::Err() << L"wide text" << std::wstring(L" - std::wstring") << " - ascii text" << std::string(" - std::string");

  // stx: task is to uncomment and revive this line
  // stxDebug::File(L"dump.txt") << L"Dump of data: " << Data(55, "stx data");

  return 0;
}

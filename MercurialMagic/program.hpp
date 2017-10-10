#include <nall/nall.hpp>
#include <hiro/hiro.hpp>
using namespace nall;
using namespace hiro;

#include <nall/beat/patch.hpp>

struct Program : Window {
  Program(string_vector args);

  enum ExportMethod : uint {
    GamePak,
    SD2SNES,
  };

  //program.cpp
  auto validatePack() -> bool;
  auto validateROMPatch() -> bool;

  auto setDestination() -> void;

  auto fetch(string_view name) -> maybe<Decode::ZIP::File>;
  auto fetch(unique_pointer<bpspatch>& patch) -> bool;

  auto setProgress(uint files) -> void;
  auto setEnabled(bool enabled = true) -> void;
  auto reset() -> void;

  auto information(const string& text) -> void;
  auto warning(const string& text, const string_vector& buttons) -> string;
  auto error(const string& text) -> void;
  auto error(const string& text, const string_vector& buttons) -> string;

  auto main() -> void;
  auto quit() -> void;

  //export.cpp
  auto beginExport() -> void;
  auto iterateExport() -> bool;
  auto finishExport() -> void;

  //convert.cpp
  auto convert(string path) -> bool;

  VerticalLayout layout{this};
    HorizontalLayout packLayout{&layout, Size{~0, 0}};
      Label packLabel{&packLayout, Size{100, 0}};
      LineEdit packPath{&packLayout, Size{400, 0}};
      Button packChange{&packLayout, Size{80, 0}};
    HorizontalLayout romLayout{&layout, Size{~0, 0}};
      Label romLabel{&romLayout, Size{100, 0}};
      LineEdit romPath{&romLayout, Size{400, 0}};
      Button romChange{&romLayout, Size{80, 0}};
    HorizontalLayout outputLayout{&layout, Size{~0, 0}};
      Label outputLabel{&outputLayout, Size{100, 0}};
      LineEdit outputName{&outputLayout, Size{400, 0}};
      Label outputExtLabel{&outputLayout, Size{50, 0}};
    Label selectLabel{&layout, Size{~0, 0}};
    HorizontalLayout gamepakLayout{&layout, Size{~0, 0}};
      RadioLabel gamepakExport{&gamepakLayout, Size{160, 0}};
      CheckLabel gamepakCreateManifest{&gamepakLayout, Size{320, 0}};
    HorizontalLayout sd2snesLayout{&layout, Size{~0, 0}};
      RadioLabel sd2snesExport{&sd2snesLayout, Size{160, 0}};
      CheckLabel sd2snesForceManifest{&sd2snesLayout, Size{320, 0}};
    Group exportGroup{&gamepakExport, &sd2snesExport};
    Label statusLabel{&layout, Size{~0, 0}};
    ProgressBar progressBar{&layout, Size{~0, 0}};
    HorizontalLayout buttonLayout{&layout, Size{~0, 0}};
      Button exportButton{&buttonLayout, Size{80, 0}};
      Button exitButton{&buttonLayout, Size{80, 0}};

  ExportMethod exportMethod;
  bool exportManifest;

  bool icarus;
  bool daedalus;

  bool valid;
  Decode::ZIP pack;
  vector<uint8_t> patchContents;
  unique_pointer<bpspatch> patch;

  uint zipIndex;
  vector<uint16_t> trackIDs;
  string destination;
};

extern unique_pointer<Program> program;

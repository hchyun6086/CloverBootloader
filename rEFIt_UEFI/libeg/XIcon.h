#if !defined(__XICON_H__)
#define __XICON_H__

#include "../cpp_foundation/XObjArray.h"
#include "../cpp_foundation/XString.h"
#include "XImage.h"
#include "libeg.h"

extern CONST CHAR8* IconsNames[];
extern const INTN IconsNamesSize;

class XIcon
{
public:
  INTN Id;  //for example BUILTIN_ICON_POINTER
  XString8 Name; //for example "os_moja", "vol_internal"
  XImage Image;
  XImage ImageNight;
  XBool Native;
  void *ImageSVG;  //NSVGimage*
  void *ImageSVGnight;
protected:
  XBool Empty;
public:
  XIcon(): Id(0), Name(), Image(), ImageNight(), Native(false), ImageSVG(nullptr), ImageSVGnight(nullptr), Empty(true) {};
  XIcon(INTN Id, XBool Embedded = false);
  // Initialisation of ImageSVG(other.ImageSVG), ImageSVGnight(other.ImageSVGnight) is wrong because we just copy the pointer
  XIcon(const XIcon& other) : Id(other.Id), Name(other.Name), Image(other.Image), ImageNight(other.ImageNight), Native(other.Native), ImageSVG(other.ImageSVG), ImageSVGnight(other.ImageSVGnight), Empty(other.Empty) {} ;
  ~XIcon();
  

  XBool isEmpty() const  { return Empty; }
  void setFilled() { Empty = false; }
  void setEmpty()  { Empty = true; }
  
  EFI_STATUS LoadXImage(const EFI_FILE *Dir, const XStringW& FileName); //for example LoadImage(ThemeDir, L"icons\\" + Name);
  EFI_STATUS LoadXImage(const EFI_FILE *Dir, const wchar_t* LIconName);
  EFI_STATUS LoadXImage(const EFI_FILE *Dir, const char* IconName);
  void GetEmbedded();

  // Default are not valid, as usual. We delete them. If needed, proper ones can be created
//  Icon(const Icon&) = delete;
  XIcon& operator=(const XIcon&); // = delete;
  XImage* GetBest(XBool night, XBool *free = nullptr);
};


#endif

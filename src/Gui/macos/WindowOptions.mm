#include <QWidget>
#include <Cocoa/Cocoa.h>

namespace Cocoa
{
  void changeTitleBarColor(WId winId, double red, double green, double blue, double alpha)
  {
    if (winId == 0)
      return;
    NSView* view = (NSView*)winId;
    NSWindow* window = [view window];
    window.titlebarAppearsTransparent = YES;
//    window.hasShadow = NO;
    window.backgroundColor = [NSColor colorWithRed:red green:green blue:blue alpha:alpha];
//    window.appearance = NSAppearance(named:NSAppearanceNameVibrantDark)
  }
}

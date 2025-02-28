# types
A C89 standard compliant, single header, nostdlib (no C Standard Library) type defines I use.

For more information please look at the "types.h" file or take a look at the "examples" or "tests" folder.

## Quick Start

Download or clone types.h and include it in your project.

```C
#include "types.h"

int main() {

    b32 test = true;

    assert(test == true);
    assert(sizeof(u8) == 1);
    assert(sizeof(u16) == 2);
    assert(sizeof(u32) == 4);

    return 0;
}
```

/*
 * Synopsys:
 * This .h "helper" simplifies the use of "numbered enums" (i.e., enums with explicitly-assigned integer constexps) by
 * - creating the typedef (for later use like with any other enum) and by - automatically and consistently -
 * - creating an "_enum2label" function that returns a (predefined) string for each (before-assigned) integer constexp
 *
 * The type itself is called MYNAME_t, whilst the string getter is called MYNAME_enum2label() with chosen name MYNAME.
 *
 * Notes:
 * - Usage: Do the following to define your numenum
 *   1. Set UZ_NUMENUM(n, i) to contain exactly one
 *      enum name n and at least one enum item i by
 *      means of a #define in your translation unit
 *      at hand.
 *      The enum name is set like so in the above:
 *       n(MYNAME)                                 \
 *      An enum item (with its integer equivalent,
 *      identifier and string label) is set one in
 *      a line as follows:
 *       i(int constant, identifier, string label) \
 *            [repeat as often as desired ...]     \
 *       i(last one as above, but no \ at the end)
 *   2. "Call" this file/helper by including it
 * - See uz_numberedenum_demo.c for a usage example
 * - This file is designed to be included multiple times, so no "once" pragmas...
 * - As usual with enums, make sure that your namespace is (as) clean (as needed)
 * - If the definition of the numenum is in a header file, ensure its uniqueness;
 *   otherwise, you will end up with multiple definitions of _enum2label in cases
 *   of multiple header inclusions, and, ultimatively, a linker error. Define the
 *   macro UZ_NUMENUM_NOHELPER in your numenum definition to avoid this and refer
 *   to uz_platform_cardeeprom.h (and a single define in uz_platform.c) for demo.
 */


//// Define helpers
#define UZ_NUMENUM_CC(a,b)	UZ_NUMENUM_CC2(a,b)
#define UZ_NUMENUM_CC2(a,b)	a##b

#define UZ_NUMENUM_NAMEGEN_NULL(NAME)
#define UZ_NUMENUM_ITEMGEN_ENUM(ID, NAME, LABEL) \
	NAME = ID,
#define UZ_NUMENUM_NAMEGEN_UNDERSCORET(NAME) \
	UZ_NUMENUM_CC(NAME, _t)
#define UZ_NUMENUM_ITEMGEN_NULL(ID, NAME, LABEL)
#define UZ_NUMENUM_NAMEGEN_LABELGETTER(NAME) \
	UZ_NUMENUM_CC(NAME, _enum2label)
#define UZ_NUMENUM_ITEMGEN_CASE(ID, NAME, LABEL) \
	case ID: return(LABEL); break;


//// Define the type itself

// Typedef, ...
typedef enum {
// ... predefined identifiers (with the integer constants), and ...
	UZ_NUMENUM(UZ_NUMENUM_NAMEGEN_NULL, UZ_NUMENUM_ITEMGEN_ENUM)
}
// ... the type name itself.
UZ_NUMENUM(UZ_NUMENUM_NAMEGEN_UNDERSCORET, UZ_NUMENUM_ITEMGEN_NULL)
;


//// Declare/Define _enum2label function

char*
	 UZ_NUMENUM(UZ_NUMENUM_NAMEGEN_LABELGETTER, UZ_NUMENUM_ITEMGEN_NULL)
	(UZ_NUMENUM(UZ_NUMENUM_NAMEGEN_UNDERSCORET, UZ_NUMENUM_ITEMGEN_NULL) val)
#ifdef UZ_NUMENUM_NOHELPER
 ;
#else
 {
	switch(val)
	{
		UZ_NUMENUM(UZ_NUMENUM_NAMEGEN_NULL, UZ_NUMENUM_ITEMGEN_CASE)

		default:
				return("Unknown enumitem");
				break;
	}
 }
#endif


//// Cleanup
#undef UZ_NUMENUM_NAMEGEN_NULL
#undef UZ_NUMENUM_ITEMGEN_ENUM
#undef UZ_NUMENUM_NAMEGEN_UNDERSCORET
#undef UZ_NUMENUM_ITEMGEN_NULL
#undef UZ_NUMENUM_NAMEGEN_LABELGETTER
#undef UZ_NUMENUM_ITEMGEN_CASE
#undef UZ_NUMENUM_CC
#undef UZ_NUMENUM_CC2
#undef UZ_NUMENUM
#undef UZ_NUMENUM_NOHELPER

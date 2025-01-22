// Housekeeping (you won't need that!)
#if !defined(__x86_64__)
 #include "../uz_HAL.h"
#else
 #include <stdio.h>
 #define uz_printf printf
#endif


//// Example definition of enum type and string getter:
#define UZ_NUMENUM(ENUMNAME, ENUMITEM) \
	ENUMNAME(fsmstate)								/* Define an uz_enum with a name as within () ... */ \
	ENUMITEM( 0,	IDLE,	 "Idling around...")	/* ... with these int values, IDs and labels¹ ... */ \
	ENUMITEM( 1,	FOO1,	 "Foo one")				/* ... (spread across multiple "ENUMITEMs()") ... */ \
	ENUMITEM(42,	FOO2,	 "Foo two")				/* ... and *no* \ after the end of the last line! */
// ¹) The labels are freely-chosen strings ("Hi")
#include "uz_numberedenum.h"
//// End of definition - NB: The #include is part of it

//// You can do this multiple times (with different ENUMNAME()s, obviously)


void uz_numenum_demo()
{
	//// Example usage of enum type and string getter:
	fsmstate_t my_fsmstate = IDLE;
	uz_printf("Label of ID %3i: %s\n", my_fsmstate, fsmstate_enum2label(my_fsmstate));

	uz_printf("\n");

	//// Some testing:
	uz_printf("The following lists the labels of enum IDs 0-43:\n");
	for (int i=0; i<44; i++)
		uz_printf("   %2i: %s\n", i, fsmstate_enum2label(i));
}


//// End of examples


// More housekeeping (like on top!)...
#if defined(__x86_64__)
 int main()
 {
	uz_numenum_demo();
	return(0);
 }
#endif

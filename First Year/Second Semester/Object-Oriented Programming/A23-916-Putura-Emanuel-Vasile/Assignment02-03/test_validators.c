#include "validators.h"
#include "material.h"
#include "date.h"

#include <stdlib.h>
#include <assert.h>

void testValidateMaterial() {
	assert(!validateMaterial(0));

	Material* m1 = createMaterial("", "", 1, "22/11/2010");
	assert(!validateMaterial(m1));

	Material* m2 = createMaterial("Bread", "", 2, "11/11/2021");
	assert(!validateMaterial(m2));
	
	Material* m3 = createMaterial("Pie", "Kaufland", 0, "09/09/2021");
	assert(!validateMaterial(m3));
	
	Material* m4= createMaterial("Donnut", "Lidl", -3, "09/09/2021");
	assert(!validateMaterial(m4));

	Material* m5 = createMaterial("Tart", "La 2 pasi", 4, "09/09/2021");
	assert(validateMaterial(m5));


	destroyMaterial(m1);
	destroyMaterial(m2);
	destroyMaterial(m3);
	destroyMaterial(m4);
	destroyMaterial(m5);
}

void testValidateDate() {
	Date* d1 = createDate("05/05/2005");
	assert(validateDate(d1));

	Date* d2 = createDate("09092009");
	assert(!validateDate(d2));

	destroyDate(d1);
	destroyDate(d2);
}

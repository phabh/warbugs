package com.change_vision.jude.api.test.model;

import junit.framework.Test;

import com.change_vision.jude.api.inf.editor.TransactionManager;
import com.change_vision.jude.api.inf.exception.InvalidEditingException;
import com.change_vision.jude.api.inf.model.IAttribute;
import com.change_vision.jude.api.inf.model.IClass;
import com.change_vision.jude.api.inf.model.IMultiplicityRange;


public class IAttributeTest extends ITestCase {

    public static Test suite() {
        return suite("testModel/judeAPITest/IAttributeTest.jude", IAttributeTest.class);
    }

    public void testGetType_int() {
        IClass cls = (IClass)getElement(project.getOwnedElements(), "Class0");
        IAttribute attr = (IAttribute)getElement(cls.getAttributes(), "attribute0");
        assertEquals("int", attr.getType().getName());
        assertEquals("int", attr.getTypeExpression());
    }

    public void testGetType_int_ARRAY() {
        IClass cls = (IClass)getElement(project.getOwnedElements(), "Class0");
        IAttribute attr = (IAttribute)getElement(cls.getAttributes(), "attribute1");
        assertEquals("int", attr.getType().getName());
        assertEquals("int[]", attr.getTypeExpression());
    }

    public void testGetType_Class1() {
        IClass cls = (IClass)getElement(project.getOwnedElements(), "Class0");
        IAttribute attr = (IAttribute)getElement(cls.getAttributes(), "attribute2");
        assertEquals("Class1", attr.getType().getName());
        assertEquals("Class1", attr.getTypeExpression());
    }

    public void testGetType_Class1_ARRAY() {
        IClass cls = (IClass)getElement(project.getOwnedElements(), "Class0");
        IAttribute attr = (IAttribute)getElement(cls.getAttributes(), "attribute3");
        assertEquals("Class1", attr.getType().getName());
        assertEquals("Class1[][2]", attr.getTypeExpression());
    }

	public void testGetInitialValue_5() {
        IClass cls = (IClass)getElement(project.getOwnedElements(), "Class0");
        IAttribute attr = (IAttribute)getElement(cls.getAttributes(), "attribute0");
        assertEquals("5", attr.getInitialValue());
	}

    public void testGetInitialValue_NONE() {
        IClass cls = (IClass)getElement(project.getOwnedElements(), "Class0");
        IAttribute attr = (IAttribute)getElement(cls.getAttributes(), "attribute1");
        assertEquals("", attr.getInitialValue());
    }

	public void testIsChangeable_true() {
        IClass cls = (IClass)getElement(project.getOwnedElements(), "Class0");
        IAttribute attr = (IAttribute)getElement(cls.getAttributes(), "attribute4");
        assertFalse(attr.isChangeable());
	}

    public void testIsChangeable_false() {
        IClass cls = (IClass)getElement(project.getOwnedElements(), "Class0");
        IAttribute attr = (IAttribute)getElement(cls.getAttributes(), "attribute0");
        assertTrue(attr.isChangeable());
    }

    public void testIsChangeable_true_ASSOCIATION_END() {
        IClass cls = (IClass)getElement(project.getOwnedElements(), "Class4");
        IAttribute attr = (IAttribute)getElement(cls.getAttributes(), "class5");
        assertFalse(attr.isChangeable());
    }

    public void testIsChangeable_false_ASSOCIATION_END() {
        IClass cls = (IClass)getElement(project.getOwnedElements(), "Class5");
        IAttribute attr = (IAttribute)getElement(cls.getAttributes(), "class4");
        assertTrue(attr.isChangeable());
    }

    public void testIsDerived_true() {
        IClass cls = (IClass)getElement(project.getOwnedElements(), "Class0");
        IAttribute attr = (IAttribute)getElement(cls.getAttributes(), "attribute5");
        assertTrue(attr.isDerived());
	}

    public void testIsDerived_false() {
        IClass cls = (IClass)getElement(project.getOwnedElements(), "Class0");
        IAttribute attr = (IAttribute)getElement(cls.getAttributes(), "attribute0");
        assertFalse(attr.isDerived());
    }

    public void testIsDerived_true_ASSOCIATION_END() {
        IClass cls = (IClass)getElement(project.getOwnedElements(), "Class2");
        IAttribute attr = (IAttribute)getElement(cls.getAttributes(), "class3");
        assertTrue(attr.isDerived());
    }

    public void testIsStatic_true() {
        IClass cls = (IClass)getElement(project.getOwnedElements(), "Class0");
        IAttribute attr = (IAttribute)getElement(cls.getAttributes(), "attribute4");
        assertTrue(attr.isStatic());
    }

    public void testIsStatic_false() {
        IClass cls = (IClass)getElement(project.getOwnedElements(), "Class0");
        IAttribute attr = (IAttribute)getElement(cls.getAttributes(), "attribute5");
        assertFalse(attr.isStatic());
    }

    public void testIsStatic_true_ASSOCIATION_END() {
        IClass cls = (IClass)getElement(project.getOwnedElements(), "Class4");
        IAttribute attr = (IAttribute)getElement(cls.getAttributes(), "class5");
        assertTrue(attr.isStatic());
    }

    public void testIsStatic_false_ASSOCIATION_END() {
        IClass cls = (IClass)getElement(project.getOwnedElements(), "Class0");
        IAttribute attr = (IAttribute)getElement(cls.getAttributes(), "class1");
        assertFalse(attr.isStatic());
    }

    public void testGetAssociation() {
        IClass cls = (IClass)getElement(project.getOwnedElements(), "Class0");
        IAttribute attr = (IAttribute)getElement(cls.getAttributes(), "class1");
        assertNotNull(attr.getAssociation());
    }

    public void testMultiplicity_None() {
        IClass cls = (IClass)getElement(project.getOwnedElements(), "Class0");
        IAttribute attr = (IAttribute)getElement(cls.getAttributes(), "class1");
        assertEquals(IMultiplicityRange.UNDEFINED, attr.getMultiplicity()[0].getLower());
        assertEquals(IMultiplicityRange.UNDEFINED, attr.getMultiplicity()[0].getUpper());
    }

    public void testMultiplicity_ASTERISK() {
        IClass cls = (IClass)getElement(project.getOwnedElements(), "Class4");
        IAttribute attr = (IAttribute)getElement(cls.getAttributes(), "class5");
        assertEquals(IMultiplicityRange.UNLIMITED, attr.getMultiplicity()[0].getLower());
        assertEquals(IMultiplicityRange.UNLIMITED, attr.getMultiplicity()[0].getUpper());
    }

    public void testMultiplicity_0_1() {
        IClass cls = (IClass)getElement(project.getOwnedElements(), "Class2");
        IAttribute attr = (IAttribute)getElement(cls.getAttributes(), "class3");
        assertEquals(0, attr.getMultiplicity()[0].getLower());
        assertEquals(1, attr.getMultiplicity()[0].getUpper());
    }

    public void testMultiplicity_ATTRIBUTE() {
        IClass cls = (IClass)getElement(project.getOwnedElements(), "Class0");
        IAttribute attr = (IAttribute)getElement(cls.getAttributes(), "attribute0");
        assertEquals(0, attr.getMultiplicity().length);
    }

	public void testIsComposite_true() {
        IClass cls = (IClass)getElement(project.getOwnedElements(), "Class5");
        IAttribute attr = (IAttribute)getElement(cls.getAttributes(), "class4");
		assertTrue(attr.isComposite());
	}

    public void testIsComposite_false_1() {
        IClass cls = (IClass)getElement(project.getOwnedElements(), "Class4");
        IAttribute attr = (IAttribute)getElement(cls.getAttributes(), "class5");
        assertFalse(attr.isComposite());
    }

    public void testIsComposite_false_2() {
        IClass cls = (IClass)getElement(project.getOwnedElements(), "Class1");
        IAttribute attr = (IAttribute)getElement(cls.getAttributes(), "class0");
        assertFalse(attr.isComposite());
    }

	public void testIsAggregate_true() {
        IClass cls = (IClass)getElement(project.getOwnedElements(), "Class3");
        IAttribute attr = (IAttribute)getElement(cls.getAttributes(), "class2");
        assertTrue(attr.isAggregate());
	}

    public void testIsAggregate_false_1() {
        IClass cls = (IClass)getElement(project.getOwnedElements(), "Class1");
        IAttribute attr = (IAttribute)getElement(cls.getAttributes(), "class0");
        assertFalse(attr.isAggregate());
    }

    public void testIsAggregate_false_2() {
        IClass cls = (IClass)getElement(project.getOwnedElements(), "Class5");
        IAttribute attr = (IAttribute)getElement(cls.getAttributes(), "class4");
        assertFalse(attr.isAggregate());
    }

    public void testIsEnable_true() {
        IClass cls = (IClass)getElement(project.getOwnedElements(), "Class5");
        IAttribute attr = (IAttribute)getElement(cls.getAttributes(), "class4");
        assertTrue(attr.isEnable());
    }

    public void testIsEnable_false() {
        IClass cls = (IClass)getElement(project.getOwnedElements(), "Class1");
        IAttribute attr = (IAttribute)getElement(cls.getAttributes(), "class0");
        assertFalse(attr.isEnable());
    }

    public void testQualifiers() {
        IClass cls = (IClass)getElement(project.getOwnedElements(), "Class0");
        IAttribute attr = (IAttribute)getElement(cls.getAttributes(), "class1");
        IAttribute[] qualifiers = attr.getQualifiers();
        assertEquals(2, attr.getQualifiers().length);
        assertEquals("key0", qualifiers[0].getName());
        assertEquals("int", qualifiers[0].getType().getName());
        assertEquals("key1", qualifiers[1].getName());
    }

    public void testQualifiers_None() {
        IClass cls = (IClass)getElement(project.getOwnedElements(), "Class1");
        IAttribute attr = (IAttribute)getElement(cls.getAttributes(), "class0");
        assertEquals(0, attr.getQualifiers().length);
    }

    public void testGetOwner() {
        IClass cls = (IClass)getElement(project.getOwnedElements(), "Class0");
        IAttribute attr = (IAttribute)getElement(cls.getAttributes(), "attribute0");
        assertEquals(cls, attr.getOwner());
    }

    public void testGetOwner_ASSOCIATION_END() {
        IClass cls = (IClass)getElement(project.getOwnedElements(), "Class0");
        IAttribute attr = (IAttribute)getElement(cls.getAttributes(), "class1");
        assertEquals(cls, attr.getOwner());
    }

    public void testIsPrivateVisibility_true() {
        IClass cls = (IClass)getElement(project.getOwnedElements(), "Class0");
        IAttribute attr = (IAttribute)getElement(cls.getAttributes(), "attribute0");
        assertTrue(attr.isPrivateVisibility());
    }

    public void testIsPrivateVisibility_false() {
        IClass cls = (IClass)getElement(project.getOwnedElements(), "Class0");
        IAttribute attr = (IAttribute)getElement(cls.getAttributes(), "attribute1");
        assertFalse(attr.isPrivateVisibility());
    }

    public void testIsPrivateVisibility_true_ASSOCIATION_END() {
        IClass cls = (IClass)getElement(project.getOwnedElements(), "Class0");
        IAttribute attr = (IAttribute)getElement(cls.getAttributes(), "class1");
        assertTrue(attr.isPrivateVisibility());
    }

    public void testIsProtectedVisibility_true() {
        IClass cls = (IClass)getElement(project.getOwnedElements(), "Class0");
        IAttribute attr = (IAttribute)getElement(cls.getAttributes(), "attribute1");
        assertTrue(attr.isProtectedVisibility());
    }

    public void testIsProtectedVisibility_false() {
        IClass cls = (IClass)getElement(project.getOwnedElements(), "Class0");
        IAttribute attr = (IAttribute)getElement(cls.getAttributes(), "attribute2");
        assertFalse(attr.isProtectedVisibility());
    }

    public void testIsProtectedVisibility_true_ASSOCIATION_END() {
        IClass cls = (IClass)getElement(project.getOwnedElements(), "Class2");
        IAttribute attr = (IAttribute)getElement(cls.getAttributes(), "class3");
        assertTrue(attr.isProtectedVisibility());
    }

    public void testIsPublicVisibility_true() {
        IClass cls = (IClass)getElement(project.getOwnedElements(), "Class0");
        IAttribute attr = (IAttribute)getElement(cls.getAttributes(), "attribute2");
        assertTrue(attr.isPublicVisibility());
    }

    public void testIsPublicVisibility_false() {
        IClass cls = (IClass)getElement(project.getOwnedElements(), "Class0");
        IAttribute attr = (IAttribute)getElement(cls.getAttributes(), "attribute3");
        assertFalse(attr.isPublicVisibility());
    }

    public void testIsPublicVisibility_true_ASSOCIATION_END() {
        IClass cls = (IClass)getElement(project.getOwnedElements(), "Class4");
        IAttribute attr = (IAttribute)getElement(cls.getAttributes(), "class5");
        assertTrue(attr.isPublicVisibility());
    }

    public void testIsPackageVisibility_true() {
        IClass cls = (IClass)getElement(project.getOwnedElements(), "Class0");
        IAttribute attr = (IAttribute)getElement(cls.getAttributes(), "attribute3");
        assertTrue(attr.isPackageVisibility());
    }

    public void testIsPackageVisibility_false() {
        IClass cls = (IClass)getElement(project.getOwnedElements(), "Class0");
        IAttribute attr = (IAttribute)getElement(cls.getAttributes(), "attribute0");
        assertFalse(attr.isPackageVisibility());
    }

    public void testIsPackageVisibility_true_ASSOCIATION_END() {
        IClass cls = (IClass)getElement(project.getOwnedElements(), "Class5");
        IAttribute attr = (IAttribute)getElement(cls.getAttributes(), "class4");
        assertTrue(attr.isPackageVisibility());
    }

    public void testSetTypeWithNullParameter() throws ClassNotFoundException {
    	IClass cls = (IClass)getElement(project.getOwnedElements(), "Class0");
        IAttribute attr = (IAttribute)getElement(cls.getAttributes(), "attribute0");
		try {
    		TransactionManager.beginTransaction();
    		attr.setType(null);
            TransactionManager.endTransaction();
            fail();
    	} catch (InvalidEditingException e) {
    		TransactionManager.abortTransaction();
    		assertEquals(e.getKey(), InvalidEditingException.PARAMETER_ERROR_KEY);
        }
	}

    public void testSetType() throws ClassNotFoundException {
    	IClass cls = (IClass)getElement(project.getOwnedElements(), "Class0");
        IAttribute attr = (IAttribute)getElement(cls.getAttributes(), "attribute0");
    	IClass cls2 = (IClass)getElement(project.getOwnedElements(), "Class2");
    	try {
    		TransactionManager.beginTransaction();
    		attr.setType(cls2);
            TransactionManager.endTransaction();
            assertEquals("Class2", attr.getType().getName());
            assertEquals("Class2", attr.getTypeExpression());
    	} catch (InvalidEditingException e) {
    		TransactionManager.abortTransaction();
    		fail();
        }
    }

    public void testSetTypeExpressionWithNullParameter() throws ClassNotFoundException {
    	IClass cls = (IClass)getElement(project.getOwnedElements(), "Class0");
        IAttribute attr = (IAttribute)getElement(cls.getAttributes(), "attribute0");
		try {
    		TransactionManager.beginTransaction();
    		attr.setTypeExpression(null);
            TransactionManager.endTransaction();
            fail();
    	} catch (InvalidEditingException e) {
    		TransactionManager.abortTransaction();
    		assertEquals(e.getKey(), InvalidEditingException.PARAMETER_ERROR_KEY);
        }
	}

    public void testSetTypeExpression() throws ClassNotFoundException {
    	IClass cls = (IClass)getElement(project.getOwnedElements(), "Class0");
        IAttribute attr = (IAttribute)getElement(cls.getAttributes(), "attribute0");
		try {
    		TransactionManager.beginTransaction();
    		attr.setTypeExpression("Class5");
            TransactionManager.endTransaction();
            assertEquals("Class5", attr.getType().getName());
            assertEquals("Class5", attr.getTypeExpression());
    	} catch (InvalidEditingException e) {
    		TransactionManager.abortTransaction();
    		fail();
        }
	}

    public void testSetTypeExpressionWithMissingClass() throws ClassNotFoundException {
    	IClass cls = (IClass)getElement(project.getOwnedElements(), "Class0");
        IAttribute attr = (IAttribute)getElement(cls.getAttributes(), "attribute0");
		try {
    		TransactionManager.beginTransaction();
    		attr.setTypeExpression("Class100");
            TransactionManager.endTransaction();
            fail();
    	} catch (InvalidEditingException e) {
    		TransactionManager.abortTransaction();
    		assertEquals(e.getKey(), InvalidEditingException.NO_TARGET_CLASSIFIER_KEY);
        }
	}

    public void testSetInitialValueWithNullParameter() throws ClassNotFoundException {
    	IClass cls = (IClass)getElement(project.getOwnedElements(), "Class0");
        IAttribute attr = (IAttribute)getElement(cls.getAttributes(), "attribute0");
		try {
    		TransactionManager.beginTransaction();
    		attr.setInitialValue(null);
            TransactionManager.endTransaction();
            assertEquals("", attr.getInitialValue());
    	} catch (InvalidEditingException e) {
    		TransactionManager.abortTransaction();
    		fail();
        }
	}

    public void testSetInitialValueForAttribute() throws ClassNotFoundException {
        setInitialValueFor(getAttribute0InClass0());
	}

    public void testSetInitialValueForAssociationEnd() throws ClassNotFoundException {
        setInitialValueFor(getAssociationEndNamedClass1());
	}

    public void testSetChangeableForAttribute() throws ClassNotFoundException {
    	setChangeableFor(getAttribute0InClass0());
    }

    public void testSetChangeableForAssociationEnd() throws ClassNotFoundException {
        setChangeableFor(getAssociationEndNamedClass1());
    }

    public void testSetAggregationForAttribute() throws ClassNotFoundException {
    	setAggregationFor(getAttribute0InClass0());
    }

    public void testSetAggregationForAssociationEnd() throws ClassNotFoundException {
    	setAggregationFor(getAssociationEndNamedClass1());
    }

    public void testSetCompositeForAttribute() throws ClassNotFoundException {
    	setCompositeFor(getAttribute0InClass0());
    }

    public void testSetCompositeForAssociationEnd() throws ClassNotFoundException {
    	setCompositeFor(getAssociationEndNamedClass1());
    }

    public void testSetStaticForAttribute() throws ClassNotFoundException {
    	setStaticFor(getAttribute0InClass0());
    }

    public void testSetStaticForAssociationEnd() throws ClassNotFoundException {
    	setStaticFor(getAssociationEndNamedClass1());
    }

    public void testSetMultiplicityWithNullParameter() throws ClassNotFoundException {
    	IAttribute attr = getAssociationEndNamedClass1();
		try {
    		TransactionManager.beginTransaction();
    		attr.setMultiplicity(null);
            TransactionManager.endTransaction();
            fail();
    	} catch (InvalidEditingException e) {
    		TransactionManager.abortTransaction();
    		assertEquals(e.getKey(), InvalidEditingException.PARAMETER_ERROR_KEY);
        }
	}

    public void testSetMultiplicityForAssociationEnd() throws ClassNotFoundException {
    	IAttribute attr = getAssociationEndNamedClass1();
    	//"0..*"
		try {
    		TransactionManager.beginTransaction();
    		attr.setMultiplicity(new int[][] {{0, IMultiplicityRange.UNLIMITED}});
            TransactionManager.endTransaction();
            assertNotNull(attr.getMultiplicity());
            assertTrue(attr.getMultiplicity().length == 1);
            assertTrue(0 == attr.getMultiplicity()[0].getLower());
            assertTrue(IMultiplicityRange.UNLIMITED == attr.getMultiplicity()[0].getUpper());
    	} catch (InvalidEditingException e) {
    		TransactionManager.abortTransaction();
    		fail();
        }
    	//"*"
    	try {
    		TransactionManager.beginTransaction();
    		attr.setMultiplicity(new int[][] {{IMultiplicityRange.UNLIMITED}});
            TransactionManager.endTransaction();
            assertNotNull(attr.getMultiplicity());
            assertTrue(attr.getMultiplicity().length == 1);
            assertTrue(IMultiplicityRange.UNLIMITED == attr.getMultiplicity()[0].getLower());
            assertTrue(IMultiplicityRange.UNLIMITED == attr.getMultiplicity()[0].getUpper());
    	} catch (InvalidEditingException e) {
    		TransactionManager.abortTransaction();
    		fail();
        }
    	//"0..6"
    	try {
    		TransactionManager.beginTransaction();
    		attr.setMultiplicity(new int[][] {{0, 6}});
            TransactionManager.endTransaction();
            assertNotNull(attr.getMultiplicity());
            assertTrue(attr.getMultiplicity().length == 1);
            assertTrue(0 == attr.getMultiplicity()[0].getLower());
            assertTrue(6 == attr.getMultiplicity()[0].getUpper());
    	} catch (InvalidEditingException e) {
    		TransactionManager.abortTransaction();
    		fail();
        }
    	//"1,3,5,7,9,0..6"
    	try {
    		TransactionManager.beginTransaction();
    		attr.setMultiplicity(new int[][] {{1},{3},{5},{7}, {9},{0,6}});
            TransactionManager.endTransaction();
            assertNotNull(attr.getMultiplicity());
            assertTrue(attr.getMultiplicity().length == 6);
            assertTrue(1 == attr.getMultiplicity()[0].getLower());
            assertTrue(1 == attr.getMultiplicity()[0].getUpper());
            assertTrue(0 == attr.getMultiplicity()[5].getLower());
            assertTrue(6 == attr.getMultiplicity()[5].getUpper());
    	} catch (InvalidEditingException e) {
    		TransactionManager.abortTransaction();
    		fail();
        }
	}

    public void testSetIllealMultiplicityForAssociationEnd() throws ClassNotFoundException {
        IAttribute attr = getAssociationEndNamedClass1();
        try {
    		TransactionManager.beginTransaction();
    		attr.setMultiplicity(new int[][] {{0, 6, 9}});
            TransactionManager.endTransaction();
            fail();
    	} catch (InvalidEditingException e) {
    		TransactionManager.abortTransaction();
    		assertEquals(e.getKey(), InvalidEditingException.INVALID_MULTIPLICITY_KEY);
        }

    	try {
    		TransactionManager.beginTransaction();
    		attr.setMultiplicity(new int[][] {{-5, 5}});
            TransactionManager.endTransaction();
            fail();
    	} catch (InvalidEditingException e) {
    		TransactionManager.abortTransaction();
    		assertEquals(e.getKey(), InvalidEditingException.INVALID_MULTIPLICITY_KEY);
        }

    	try {
    		TransactionManager.beginTransaction();
    		attr.setMultiplicity(new int[][] {{0, -5}});
            TransactionManager.endTransaction();
            fail();
    	} catch (InvalidEditingException e) {
    		TransactionManager.abortTransaction();
    		assertEquals(e.getKey(), InvalidEditingException.INVALID_MULTIPLICITY_KEY);
        }

    	try {
    		TransactionManager.beginTransaction();
    		attr.setMultiplicity(new int[][] {{10, 5}});
            TransactionManager.endTransaction();
            fail();
    	} catch (InvalidEditingException e) {
    		TransactionManager.abortTransaction();
    		assertEquals(e.getKey(), InvalidEditingException.INVALID_MULTIPLICITY_KEY);
        }
    }

    public void testSetIsDerivedForAttribute() throws ClassNotFoundException {
    	setDerivedFor(getAttribute0InClass0());
    }

    public void testSetIsDerivedForAssociationEnd() throws ClassNotFoundException {
    	setDerivedFor(getAssociationEndNamedClass1());
    }

    public void testSetIsEnableForAssociationEnd() throws ClassNotFoundException {
        IAttribute attr = getAssociationEndNamedClass1();
		try {
    		TransactionManager.beginTransaction();
    		attr.setEnable(false);
            TransactionManager.endTransaction();
            assertFalse(attr.isEnable());
    	} catch (InvalidEditingException e) {
    		TransactionManager.abortTransaction();
    		fail();
        }
    	try {
    		TransactionManager.beginTransaction();
    		attr.setEnable(true);
            TransactionManager.endTransaction();
            assertTrue(attr.isEnable());
    	} catch (InvalidEditingException e) {
    		TransactionManager.abortTransaction();
    		fail();
        }
    }

    private IAttribute getAttribute0InClass0() {
    	IClass cls = (IClass)getElement(project.getOwnedElements(), "Class0");
        return (IAttribute)getElement(cls.getAttributes(), "attribute0");
    }

    private IAttribute getAssociationEndNamedClass1() {
    	IClass cls = (IClass)getElement(project.getOwnedElements(), "Class0");
        return (IAttribute)getElement(cls.getAttributes(), "class1");
    }

    private void setInitialValueFor(IAttribute attr) throws ClassNotFoundException {
    	try {
    		TransactionManager.beginTransaction();
    		attr.setInitialValue("10");
            TransactionManager.endTransaction();
            assertEquals("10", attr.getInitialValue());
    	} catch (InvalidEditingException e) {
    		TransactionManager.abortTransaction();
    		fail();
        }
    	try {
    		TransactionManager.beginTransaction();
    		attr.setInitialValue("");
            TransactionManager.endTransaction();
            assertEquals("", attr.getInitialValue());
    	} catch (InvalidEditingException e) {
    		TransactionManager.abortTransaction();
    		fail();
        }
    }

    private void setChangeableFor(IAttribute attr) throws ClassNotFoundException {
    	try {
    		TransactionManager.beginTransaction();
    		attr.setChangeable(false);
            TransactionManager.endTransaction();
            assertFalse(attr.isChangeable());
    	} catch (InvalidEditingException e) {
    		TransactionManager.abortTransaction();
    		fail();
        }
    	try {
    		TransactionManager.beginTransaction();
    		attr.setChangeable(true);
            TransactionManager.endTransaction();
            assertTrue(attr.isChangeable());
    	} catch (InvalidEditingException e) {
    		TransactionManager.abortTransaction();
    		fail();
        }
    }

    private void setAggregationFor(IAttribute attr) throws ClassNotFoundException {
    	try {
    		TransactionManager.beginTransaction();
    		attr.setComposite();
    		attr.setAggregation();
            TransactionManager.endTransaction();
            assertTrue(attr.isAggregate());
            assertFalse(attr.isComposite());
    	} catch (InvalidEditingException e) {
    		TransactionManager.abortTransaction();
    		fail();
        }
    	try {
    		TransactionManager.beginTransaction();
    		attr.setAggregation();
            TransactionManager.endTransaction();
            assertFalse(attr.isAggregate());
            assertFalse(attr.isComposite());
    	} catch (InvalidEditingException e) {
    		TransactionManager.abortTransaction();
    		fail();
        }
    }

    private void setCompositeFor(IAttribute attr) throws ClassNotFoundException {
    	try {
    		TransactionManager.beginTransaction();
    		attr.setAggregation();
    		attr.setComposite();
            TransactionManager.endTransaction();
            assertTrue(attr.isComposite());
            assertFalse(attr.isAggregate());
    	} catch (InvalidEditingException e) {
    		TransactionManager.abortTransaction();
    		fail();
        }
    	try {
    		TransactionManager.beginTransaction();
    		attr.setComposite();
            TransactionManager.endTransaction();
            assertFalse(attr.isComposite());
            assertFalse(attr.isAggregate());
    	} catch (InvalidEditingException e) {
    		TransactionManager.abortTransaction();
    		fail();
        }
    }

    private void setStaticFor(IAttribute attr) throws ClassNotFoundException {
    	try {
    		TransactionManager.beginTransaction();
    		attr.setStatic(true);
            TransactionManager.endTransaction();
            assertTrue(attr.isStatic());
    	} catch (InvalidEditingException e) {
    		TransactionManager.abortTransaction();
    		fail();
        }
    	try {
    		TransactionManager.beginTransaction();
    		attr.setStatic(false);
            TransactionManager.endTransaction();
            assertFalse(attr.isStatic());
    	} catch (InvalidEditingException e) {
    		TransactionManager.abortTransaction();
    		fail();
        }
    }

    private void setDerivedFor(IAttribute attr) throws ClassNotFoundException {
    	try {
    		TransactionManager.beginTransaction();
    		attr.setDerived(true);
            TransactionManager.endTransaction();
            assertTrue(attr.isDerived());
    	} catch (InvalidEditingException e) {
    		TransactionManager.abortTransaction();
    		fail();
        }
    	try {
    		TransactionManager.beginTransaction();
    		attr.setDerived(false);
            TransactionManager.endTransaction();
            assertFalse(attr.isDerived());
    	} catch (InvalidEditingException e) {
    		TransactionManager.abortTransaction();
    		fail();
        }
    }

    public void testSetMultiplicityRange() throws ClassNotFoundException {
        try {
            IClass cls = (IClass)getElement(project.getOwnedElements(), "Class2");
            IAttribute attr = (IAttribute)getElement(cls.getAttributes(), "class3");
            attr.getMultiplicity()[0].setUpper(10);
            attr.getMultiplicity()[0].setLower(1);
            assertEquals(1, attr.getMultiplicity()[0].getLower());
            assertEquals(10, attr.getMultiplicity()[0].getUpper());
        } catch (InvalidEditingException e) {
            TransactionManager.abortTransaction();
            fail();
        }
    }

    public void testSetMultiplicityRangeIllegal() throws ClassNotFoundException {
        try {
            IClass cls = (IClass)getElement(project.getOwnedElements(), "Class2");
            IAttribute attr = (IAttribute)getElement(cls.getAttributes(), "class3");
            attr.getMultiplicity()[0].setLower(15);
            attr.getMultiplicity()[0].setUpper(10);
            fail();
            TransactionManager.abortTransaction();
        } catch (InvalidEditingException e) {
            TransactionManager.abortTransaction();
            assertEquals(e.getKey(), InvalidEditingException.PARAMETER_ERROR_KEY);
        }
    }

    public void testSetMultiplicityRangeIllegal2() throws ClassNotFoundException {
        try {
            IClass cls = (IClass)getElement(project.getOwnedElements(), "Class2");
            IAttribute attr = (IAttribute)getElement(cls.getAttributes(), "class3");
            attr.getMultiplicity()[0].setLower(-5);
            attr.getMultiplicity()[0].setUpper(10);
            fail();
            TransactionManager.abortTransaction();
        } catch (InvalidEditingException e) {
            TransactionManager.abortTransaction();
            assertEquals(e.getKey(), InvalidEditingException.PARAMETER_ERROR_KEY);
        }
    }
}

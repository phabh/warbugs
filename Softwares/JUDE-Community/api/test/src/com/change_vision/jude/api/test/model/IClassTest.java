package com.change_vision.jude.api.test.model;

import junit.framework.Test;

import com.change_vision.jude.api.inf.editor.TransactionManager;
import com.change_vision.jude.api.inf.exception.InvalidEditingException;
import com.change_vision.jude.api.inf.model.IClass;
import com.change_vision.jude.api.inf.model.IClassifierTemplateParameter;
import com.change_vision.jude.api.inf.model.ITemplateBinding;

public class IClassTest extends ITestCase {

    public static Test suite() {
        return suite("testModel/judeAPITest/IClassTest.jude", IClassTest.class);
    }

    public void testIsAbstract_true() {
        IClass cls = (IClass)getElement(project.getOwnedElements(), "Class0");
        assertTrue(cls.isAbstract());
    }

    public void testIsAbstract_false() {
        IClass cls = (IClass)getElement(project.getOwnedElements(), "Class1");
        assertFalse(cls.isAbstract());
    }

    public void testIsLeaf_true() {
        IClass cls = (IClass)getElement(project.getOwnedElements(), "Class1");
        assertTrue(cls.isLeaf());
    }

    public void testIsLeaf_false() {
        IClass cls = (IClass)getElement(project.getOwnedElements(), "Class0");
        assertFalse(cls.isLeaf());
    }

    public void testIsActive_true() {
        IClass cls = (IClass)getElement(project.getOwnedElements(), "Class1");
        assertTrue(cls.isActive());
    }

    public void testIsActive_false() {
        IClass cls = (IClass)getElement(project.getOwnedElements(), "Class0");
        assertFalse(cls.isActive());
    }

    public void testGetAttributes() {
        IClass cls = (IClass)getElement(project.getOwnedElements(), "Class0");
        assertEquals(2, cls.getAttributes().length);
	}

	public void testGetOperations() {
        IClass cls = (IClass)getElement(project.getOwnedElements(), "Class0");
        assertEquals(2, cls.getOperations().length);
	}

	public void testGetNestedClasses() {
        IClass cls = (IClass)getElement(project.getOwnedElements(), "Class0");
        assertEquals(2, cls.getNestedClasses().length);
	}

	public void testGetGeneralizations() {
        IClass cls = (IClass)getElement(project.getOwnedElements(), "Class5");
        assertEquals(2, cls.getGeneralizations().length);
        assertEquals("3-5", cls.getGeneralizations()[0].getName());
        assertEquals("4-5", cls.getGeneralizations()[1].getName());
	}

	public void testGetSpecializations() {
        IClass cls = (IClass)getElement(project.getOwnedElements(), "Class5");
        assertEquals(2, cls.getSpecializations().length);
        assertEquals("5-6", cls.getSpecializations()[0].getName());
        assertEquals("5-7", cls.getSpecializations()[1].getName());
	}

	public void testSupplierRealizations() {
        IClass cls = (IClass)getElement(project.getOwnedElements(), "Interface1");
        assertEquals(2, cls.getSupplierRealizations().length);
        assertEquals("I1-C8", cls.getSupplierRealizations()[0].getName());
        assertEquals("I1-C9", cls.getSupplierRealizations()[1].getName());
	}

	public void testClientRealizations() {
        IClass cls = (IClass)getElement(project.getOwnedElements(), "Class8");
        assertEquals(2, cls.getClientRealizations().length);
        assertEquals("I0-C8", cls.getClientRealizations()[0].getName());
        assertEquals("I1-C8", cls.getClientRealizations()[1].getName());
	}

	public void testSupplierUsages() {
        IClass cls = (IClass)getElement(project.getOwnedElements(), "Interface2");
        assertEquals(1, cls.getSupplierUsages().length);
        assertEquals("Usage", cls.getSupplierUsages()[0].getName());
	}

	public void testClientUsages() {
        IClass cls = (IClass)getElement(project.getOwnedElements(), "Class10");
        assertEquals(1, cls.getClientUsages().length);
        assertEquals("Usage", cls.getClientUsages()[0].getName());
	}

	public void testSetAbstract() throws ClassNotFoundException {
		IClass cls = (IClass)getElement(project.getOwnedElements(), "Class0");
		try {
        	TransactionManager.beginTransaction();
        	cls.setAbstract(true);
        	TransactionManager.endTransaction();
        	assertTrue(cls.isAbstract());
        } catch (InvalidEditingException e) {
			TransactionManager.abortTransaction();
			fail();
		}

        try {
        	TransactionManager.beginTransaction();
        	cls.setAbstract(false);
        	TransactionManager.endTransaction();
        	assertFalse(cls.isAbstract());
        } catch (InvalidEditingException e) {
			TransactionManager.abortTransaction();
			fail();
		}
	}

	public void testSetLeafError() throws ClassNotFoundException {
		IClass cls = (IClass)getElement(project.getOwnedElements(), "Class3"); //3-5
		try {
        	TransactionManager.beginTransaction();
        	cls.setLeaf(true);
        	TransactionManager.endTransaction();
        	fail();
        } catch (InvalidEditingException e) {
			TransactionManager.abortTransaction();
			assertEquals(e.getKey(),InvalidEditingException.LEAF_ERROR_KEY);
		}
	}

	public void testSetLeaf() throws ClassNotFoundException {
		IClass cls = (IClass)getElement(project.getOwnedElements(), "Class0");
		try {
        	TransactionManager.beginTransaction();
        	cls.setLeaf(true);
        	TransactionManager.endTransaction();
        	assertTrue(cls.isLeaf());
        } catch (InvalidEditingException e) {
			TransactionManager.abortTransaction();
			fail();
		}

        try {
        	TransactionManager.beginTransaction();
        	cls.setLeaf(false);
        	TransactionManager.endTransaction();
        	assertFalse(cls.isLeaf());
        } catch (InvalidEditingException e) {
			TransactionManager.abortTransaction();
			fail();
		}
	}

	public void testSetActive() throws ClassNotFoundException {
		IClass cls = (IClass)getElement(project.getOwnedElements(), "Class0");
		try {
        	TransactionManager.beginTransaction();
        	cls.setActive(true);
        	TransactionManager.endTransaction();
        	assertTrue(cls.isActive());
        } catch (InvalidEditingException e) {
			TransactionManager.abortTransaction();
			fail();
		}

        try {
        	TransactionManager.beginTransaction();
        	cls.setActive(false);
        	TransactionManager.endTransaction();
        	assertFalse(cls.isActive());
        } catch (InvalidEditingException e) {
			TransactionManager.abortTransaction();
			fail();
		}
	}
	
	public void testgetTemplateParameter() throws ClassNotFoundException {
		IClass cls = (IClass)getElement(project.getOwnedElements(), "Class1");
        IClassifierTemplateParameter[] templateParameters = cls.getTemplateParameters();
        assertEquals(1,templateParameters.length);
        assertEquals("T",templateParameters[0].getName());
	}
	
	public void testgetTemplateBinding() throws ClassNotFoundException {
		IClass cls = (IClass)getElement(project.getOwnedElements(), "Class2");
        ITemplateBinding[] templateBindings = cls.getTemplateBindings();
        assertEquals(1,templateBindings.length);
	}
}

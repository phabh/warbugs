package com.change_vision.jude.api.test.model;

import junit.framework.Test;

import com.change_vision.jude.api.inf.editor.TransactionManager;
import com.change_vision.jude.api.inf.exception.InvalidEditingException;
import com.change_vision.jude.api.inf.model.IClass;
import com.change_vision.jude.api.inf.model.IOperation;
import com.change_vision.jude.api.inf.model.IParameter;

public class IOperationTest extends ITestCase {

    public static Test suite() {
        return suite("testModel/judeAPITest/IOperationTest.jude", IOperationTest.class);
    }

	public void testParameters_0() {
        IClass cls = (IClass)getElement(project.getOwnedElements(), "Class0");
        IOperation op = (IOperation)getElement(cls.getOperations(), "operation1");
        assertEquals(0, op.getParameters().length);
	}

    public void testParameters_2() {
        IClass cls = (IClass)getElement(project.getOwnedElements(), "Class0");
        IOperation op = (IOperation)getElement(cls.getOperations(), "operation3");
        assertEquals(2, op.getParameters().length);
        assertEquals("param0", op.getParameters()[0].getName());
        assertEquals("param1", op.getParameters()[1].getName());
    }

	public void testReturnType_void() {
        IClass cls = (IClass)getElement(project.getOwnedElements(), "Class0");
        IOperation op = (IOperation)getElement(cls.getOperations(), "operation1");
        assertEquals("void", op.getReturnType().getName());
        assertEquals("void", op.getReturnTypeExpression());
	}

    public void testReturnType_Class1() {
        IClass cls = (IClass)getElement(project.getOwnedElements(), "Class0");
        IOperation op = (IOperation)getElement(cls.getOperations(), "operation2");
        assertEquals("Class1", op.getReturnType().getName());
        assertEquals("Class1", op.getReturnTypeExpression());
    }

    public void testReturnType_Class1_ARRAY3() {
        IClass cls = (IClass)getElement(project.getOwnedElements(), "Class0");
        IOperation op = (IOperation)getElement(cls.getOperations(), "operation3");
        assertEquals("Class1", op.getReturnType().getName());
        assertEquals("Class1[3]", op.getReturnTypeExpression());
    }

    public void testReturnType_null() { // for constructor
        IClass cls = (IClass)getElement(project.getOwnedElements(), "Class0");
        IOperation op = (IOperation)getElement(cls.getOperations(), "operation4");
        assertEquals(null, op.getReturnType());
        assertEquals("", op.getReturnTypeExpression());
    }

    public void testIsAbstract_true() {
        IClass cls = (IClass)getElement(project.getOwnedElements(), "Class0");
        IOperation op = (IOperation)getElement(cls.getOperations(), "operation1");
        assertTrue(op.isAbstract());
	}

    public void testIsAbstract_false() {
        IClass cls = (IClass)getElement(project.getOwnedElements(), "Class0");
        IOperation op = (IOperation)getElement(cls.getOperations(), "operation0");
        assertFalse(op.isAbstract());
    }

	public void testIsStatic_true() {
        IClass cls = (IClass)getElement(project.getOwnedElements(), "Class0");
        IOperation op = (IOperation)getElement(cls.getOperations(), "operation0");
        assertTrue(op.isStatic());
	}

    public void testIsStatic_final() {
        IClass cls = (IClass)getElement(project.getOwnedElements(), "Class0");
        IOperation op = (IOperation)getElement(cls.getOperations(), "operation1");
        assertFalse(op.isStatic());
    }

    public void testIsLeaf_true() {
        IClass cls = (IClass)getElement(project.getOwnedElements(), "Class0");
        IOperation op = (IOperation)getElement(cls.getOperations(), "operation0");
        assertTrue(op.isLeaf());
    }

    public void testIsLeaf_final() {
        IClass cls = (IClass)getElement(project.getOwnedElements(), "Class0");
        IOperation op = (IOperation)getElement(cls.getOperations(), "operation1");
        assertFalse(op.isLeaf());
    }

    public void testIsPublicVisibility_true() {
        IClass cls = (IClass)getElement(project.getOwnedElements(), "Class0");
        IOperation op = (IOperation)getElement(cls.getOperations(), "operation0");
        assertTrue(op.isPublicVisibility());
    }

    public void testIsPublicVisibility_false() {
        IClass cls = (IClass)getElement(project.getOwnedElements(), "Class0");
        IOperation op = (IOperation)getElement(cls.getOperations(), "operation1");
        assertFalse(op.isPublicVisibility());
    }

    public void testIsProtectedVisibility_true() {
        IClass cls = (IClass)getElement(project.getOwnedElements(), "Class0");
        IOperation op = (IOperation)getElement(cls.getOperations(), "operation1");
        assertTrue(op.isProtectedVisibility());
    }

    public void testIsProtectedVisibility_false() {
        IClass cls = (IClass)getElement(project.getOwnedElements(), "Class0");
        IOperation op = (IOperation)getElement(cls.getOperations(), "operation2");
        assertFalse(op.isProtectedVisibility());
    }

    public void testIsPackageVisibility_true() {
        IClass cls = (IClass)getElement(project.getOwnedElements(), "Class0");
        IOperation op = (IOperation)getElement(cls.getOperations(), "operation2");
        assertTrue(op.isPackageVisibility());
    }

    public void testIsPackageVisibility_false() {
        IClass cls = (IClass)getElement(project.getOwnedElements(), "Class0");
        IOperation op = (IOperation)getElement(cls.getOperations(), "operation3");
        assertFalse(op.isPackageVisibility());
    }

    public void testIsPrivateVisibility_true() {
        IClass cls = (IClass)getElement(project.getOwnedElements(), "Class0");
        IOperation op = (IOperation)getElement(cls.getOperations(), "operation3");
        assertTrue(op.isPrivateVisibility());
    }

    public void testIsPrivateVisibility_false() {
        IClass cls = (IClass)getElement(project.getOwnedElements(), "Class0");
        IOperation op = (IOperation)getElement(cls.getOperations(), "operation0");
        assertFalse(op.isPrivateVisibility());
    }

    public void testAddParameter() throws ClassNotFoundException {
		try {
	        TransactionManager.beginTransaction();
	        IClass cls = (IClass)getElement(project.getOwnedElements(), "Class0");
	        IOperation operation3 = (IOperation)getElement(cls.getOperations(), "operation3");
	        IParameter[] ps = operation3.getParameters();
	        int operation3_parameters_length = ps.length;
	        IOperation operation2 = ((IOperation) getElement(cls.getOperations(), "operation2"));
			operation2.addParameter(ps);
			IParameter[] parameters = operation2.getParameters();
			for (int i = 0; i < parameters.length; i++) {
				IParameter p = parameters[i];
				assertEquals(p.getOwner(), operation2);
			}

	        IParameter[] ps3 = operation3.getParameters();
	        assertEquals(operation3_parameters_length, ps3.length);
			for (int i = 0; i < ps3.length; i++) {
				IParameter p = ps3[i];
				assertEquals(p.getOwner(), operation3);
			}
	        TransactionManager.endTransaction();
		} catch (InvalidEditingException e) {
			TransactionManager.abortTransaction();
			assertEquals(e.getKey(), InvalidEditingException.HAS_EXCEPTION_KEY);
		}
    }

    public void testAddParameterWithSameName() throws ClassNotFoundException {
		try {
	        TransactionManager.beginTransaction();
	        IClass cls = (IClass)getElement(project.getOwnedElements(), "Class0");
	        IOperation operation3 = (IOperation)getElement(cls.getOperations(), "operation3");
	        operation3.addParameter(operation3.getParameters());
			fail();
	        TransactionManager.endTransaction();
		} catch (InvalidEditingException e) {
			TransactionManager.abortTransaction();
			assertEquals(e.getKey(), InvalidEditingException.NAME_DOUBLE_ERROR_KEY);
		}
    }

    public void testAddParameterWithNullParameter() throws ClassNotFoundException {
		try {
	        TransactionManager.beginTransaction();
	        IClass cls = (IClass)getElement(project.getOwnedElements(), "Class0");
	        IOperation operation3 = (IOperation)getElement(cls.getOperations(), "operation3");
	        operation3.addParameter(null);
			fail();
	        TransactionManager.endTransaction();
		} catch (InvalidEditingException e) {
			TransactionManager.abortTransaction();
			assertEquals(e.getKey(), InvalidEditingException.PARAMETER_ERROR_KEY);
		}
    }

    public void testRemoveParameter() throws ClassNotFoundException {
		try {
	        TransactionManager.beginTransaction();
	        IClass cls = (IClass)getElement(project.getOwnedElements(), "Class2");
	        IOperation op = (IOperation)getElement(cls.getOperations(), "operation0");
	        op.removeParameter(op.getParameters());
	        assertEquals(0, op.getParameters().length);
	        TransactionManager.endTransaction();
		} catch (InvalidEditingException e) {
			TransactionManager.abortTransaction();
			assertEquals(e.getKey(), InvalidEditingException.HAS_EXCEPTION_KEY);
		}
    }

    public void testRemoveParameterWithErrorNamespace() throws ClassNotFoundException {
		try {
	        TransactionManager.beginTransaction();
	        IClass cls = (IClass)getElement(project.getOwnedElements(), "Class2");
	        IOperation op = (IOperation)getElement(cls.getOperations(), "operation1");
	        IOperation operation2 = ((IOperation) getElement(cls.getOperations(), "operation2"));
			operation2.removeParameter(op.getParameters());
			assertEquals(operation2.getParameters().length, 2);
	        TransactionManager.endTransaction();
		} catch (InvalidEditingException e) {
			TransactionManager.abortTransaction();
			assertEquals(e.getKey(), InvalidEditingException.HAS_EXCEPTION_KEY);
		}
    }

    public void testRemoveParameterWithNullParameter() throws ClassNotFoundException {
		try {
	        TransactionManager.beginTransaction();
	        IClass cls = (IClass)getElement(project.getOwnedElements(), "Class2");
	        IOperation operation1 = ((IOperation) getElement(cls.getOperations(), "operation1"));
			operation1.removeParameter(null);
			fail();
			TransactionManager.endTransaction();
		} catch (InvalidEditingException e) {
			TransactionManager.abortTransaction();
			assertEquals(e.getKey(), InvalidEditingException.PARAMETER_ERROR_KEY);
		}
    }

    public void testSetAbstractTrue() throws ClassNotFoundException {
		try {
	        TransactionManager.beginTransaction();
	        IClass cls = (IClass)getElement(project.getOwnedElements(), "Class2");
	        IOperation op = (IOperation)getElement(cls.getOperations(), "operation1");
	        op.setAbstract(true);
			assertEquals(op.isAbstract(), true);
	        TransactionManager.endTransaction();
		} catch (InvalidEditingException e) {
			TransactionManager.abortTransaction();
			assertEquals(e.getKey(), InvalidEditingException.HAS_EXCEPTION_KEY);
		}
    }

    public void testSetAbstractFalse() throws ClassNotFoundException {
		try {
	        TransactionManager.beginTransaction();
	        IClass cls = (IClass)getElement(project.getOwnedElements(), "Class2");
	        IOperation op = (IOperation)getElement(cls.getOperations(), "operation1");
	        op.setAbstract(false);
			assertEquals(op.isAbstract(), false);
	        TransactionManager.endTransaction();
		} catch (InvalidEditingException e) {
			TransactionManager.abortTransaction();
			assertEquals(e.getKey(), InvalidEditingException.HAS_EXCEPTION_KEY);
		}
    }

    public void testSetLeafTrue() throws ClassNotFoundException {
		try {
	        TransactionManager.beginTransaction();
	        IClass cls = (IClass)getElement(project.getOwnedElements(), "Class2");
	        IOperation op = (IOperation)getElement(cls.getOperations(), "operation1");
	        op.setLeaf(true);
			assertEquals(op.isLeaf(), true);
	        TransactionManager.endTransaction();
		} catch (InvalidEditingException e) {
			TransactionManager.abortTransaction();
			assertEquals(e.getKey(), InvalidEditingException.HAS_EXCEPTION_KEY);
		}
    }

    public void testSetLeafFalse() throws ClassNotFoundException {
		try {
	        TransactionManager.beginTransaction();
	        IClass cls = (IClass)getElement(project.getOwnedElements(), "Class2");
	        IOperation op = (IOperation)getElement(cls.getOperations(), "operation1");
	        op.setLeaf(false);
			assertEquals(op.isLeaf(), false);
	        TransactionManager.endTransaction();
		} catch (InvalidEditingException e) {
			TransactionManager.abortTransaction();
			assertEquals(e.getKey(), InvalidEditingException.HAS_EXCEPTION_KEY);
		}
    }

    public void testSetReturnType() throws ClassNotFoundException {
		try {
	        TransactionManager.beginTransaction();
	        IClass cls = (IClass)getElement(project.getOwnedElements(), "Class2");
	        IOperation op = (IOperation)getElement(cls.getOperations(), "operation1");
	        op.setReturnType(cls);
			assertEquals(op.getReturnType(), cls);
	        TransactionManager.endTransaction();
		} catch (InvalidEditingException e) {
			TransactionManager.abortTransaction();
			assertEquals(e.getKey(), InvalidEditingException.HAS_EXCEPTION_KEY);
		}
    }

    public void testSetReturnTypeWithNullParameter() throws ClassNotFoundException {
		try {
	        TransactionManager.beginTransaction();
	        IClass cls = (IClass)getElement(project.getOwnedElements(), "Class2");
	        IOperation op = (IOperation)getElement(cls.getOperations(), "operation1");
	        op.setReturnType(null);
	        fail();
	        TransactionManager.endTransaction();
		} catch (InvalidEditingException e) {
			TransactionManager.abortTransaction();
			assertEquals(e.getKey(), InvalidEditingException.PARAMETER_ERROR_KEY);
		}
    }

    public void testSetStaticTrue() throws ClassNotFoundException {
		try {
	        TransactionManager.beginTransaction();
	        IClass cls = (IClass)getElement(project.getOwnedElements(), "Class2");
	        IOperation op = (IOperation)getElement(cls.getOperations(), "operation1");
	        op.setStatic(true);
	        assertEquals(true, op.isStatic());
	        TransactionManager.endTransaction();
		} catch (InvalidEditingException e) {
			TransactionManager.abortTransaction();
			assertEquals(e.getKey(), InvalidEditingException.HAS_EXCEPTION_KEY);
		}
    }

    public void testSetStaticFalse() throws ClassNotFoundException {
		try {
	        TransactionManager.beginTransaction();
	        IClass cls = (IClass)getElement(project.getOwnedElements(), "Class2");
	        IOperation op = (IOperation)getElement(cls.getOperations(), "operation1");
	        op.setStatic(false);
	        assertEquals(false, op.isStatic());
	        TransactionManager.endTransaction();
		} catch (InvalidEditingException e) {
			TransactionManager.abortTransaction();
			assertEquals(e.getKey(), InvalidEditingException.HAS_EXCEPTION_KEY);
		}
    }
}

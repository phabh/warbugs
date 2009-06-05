package com.change_vision.jude.api.test.model;

import junit.framework.Test;

import com.change_vision.jude.api.inf.editor.TransactionManager;
import com.change_vision.jude.api.inf.exception.InvalidEditingException;
import com.change_vision.jude.api.inf.model.IClass;
import com.change_vision.jude.api.inf.model.IGeneralization;

public class IGeneralizationTest extends ITestCase {

    public static Test suite() {
        return suite("testModel/judeAPITest/IClassTest.jude", IGeneralizationTest.class);
    }

	public void testGetSubType() {
        IClass cls = (IClass)getElement(project.getOwnedElements(), "Class5");
        IGeneralization[] generalizations = cls.getGeneralizations();  // 3-5, 4-5

        assertEquals(cls, generalizations[0].getSubType());
        assertEquals(cls, generalizations[1].getSubType());
	}

	public void testGetSuperType() {
        IClass cls = (IClass)getElement(project.getOwnedElements(), "Class5");
        IGeneralization[] generalizations = cls.getGeneralizations();  // 3-5, 4-5

        IClass cls3 = (IClass)getElement(project.getOwnedElements(), "Class3");
        IClass cls4 = (IClass)getElement(project.getOwnedElements(), "Class4");

        assertEquals(cls3, generalizations[0].getSuperType());
        assertEquals(cls4, generalizations[1].getSuperType());
	}

	public void testSetSuperTypeWithNullParameter() throws ClassNotFoundException {
		IClass cls5 = (IClass)getElement(project.getOwnedElements(), "Class5");
        IGeneralization[] generalizations = cls5.getGeneralizations();  // 3-5, 4-5
		try {
    		TransactionManager.beginTransaction();
    		generalizations[0].setSuperType(null);
            TransactionManager.endTransaction();
            fail();
    	} catch (InvalidEditingException e) {
    		TransactionManager.abortTransaction();
    		assertEquals(e.getKey(), InvalidEditingException.PARAMETER_ERROR_KEY);
        }
	}

	public void testLeafErrorForSetSuperType() throws ClassNotFoundException {
		IClass cls5 = (IClass)getElement(project.getOwnedElements(), "Class5");
		IClass cls1 = (IClass)getElement(project.getOwnedElements(), "Class1"); // isLeaf == true
        IGeneralization[] generalizations = cls5.getGeneralizations();  // 3-5, 4-5
		try {
    		TransactionManager.beginTransaction();
    		generalizations[0].setSuperType(cls1);
            TransactionManager.endTransaction();
            fail();
    	} catch (InvalidEditingException e) {
    		TransactionManager.abortTransaction();
    		assertEquals(e.getKey(), InvalidEditingException.LEAF_ERROR_KEY);
        }
	}

	public void testSetSuperType() throws ClassNotFoundException {
		IClass cls5 = (IClass)getElement(project.getOwnedElements(), "Class5");
		IClass cls0 = (IClass)getElement(project.getOwnedElements(), "Class0");
        IGeneralization[] generalizations = cls5.getGeneralizations();  // 3-5, 4-5
		try {
    		TransactionManager.beginTransaction();
    		generalizations[0].setSuperType(cls0);
            TransactionManager.endTransaction();
            assertEquals(generalizations[0].getSuperType(), cls0); //0-5
    	} catch (InvalidEditingException e) {
    		TransactionManager.abortTransaction();
    		fail();
        }
	}

	public void testSetSubTypeWithNullParameter() throws ClassNotFoundException {
		IClass cls5 = (IClass)getElement(project.getOwnedElements(), "Class5");
        IGeneralization[] generalizations = cls5.getGeneralizations();  // 0-5, 4-5
		try {
    		TransactionManager.beginTransaction();
    		generalizations[0].setSubType(null);
            TransactionManager.endTransaction();
            fail();
    	} catch (InvalidEditingException e) {
    		TransactionManager.abortTransaction();
    		assertEquals(e.getKey(), InvalidEditingException.PARAMETER_ERROR_KEY);
        }
	}

	public void testSetSubType() throws ClassNotFoundException {
		IClass cls5 = (IClass)getElement(project.getOwnedElements(), "Class5");
		IClass cls4 = (IClass)getElement(project.getOwnedElements(), "Class4");
        IGeneralization[] generalizations = cls5.getGeneralizations();  // 0-5, 4-5
		try {
    		TransactionManager.beginTransaction();
    		generalizations[0].setSubType(cls4);
            TransactionManager.endTransaction();
            assertEquals(cls4, generalizations[0].getSubType()); // 0-4
    	} catch (InvalidEditingException e) {
    		TransactionManager.abortTransaction();
            fail();
        }
	}

	public void testSetSuperTypeToLoop() throws ClassNotFoundException {
		IClass cls6 = (IClass)getElement(project.getOwnedElements(), "Class6");
		IClass cls4 = (IClass)getElement(project.getOwnedElements(), "Class4");
        IGeneralization[] generalizations = cls4.getGeneralizations();  // 0-4
		try {
    		TransactionManager.beginTransaction();
    		generalizations[0].setSuperType(cls6); // 6-4,4-5,5-6
            TransactionManager.endTransaction();
            fail();
    	} catch (InvalidEditingException e) {
    		TransactionManager.abortTransaction();
    		assertEquals(e.getKey(), InvalidEditingException.CLASSIFIER_LOOP_KEY);
        }
	}

	public void testSetSubTypeToLoop() throws ClassNotFoundException {
		IClass cls7 = (IClass)getElement(project.getOwnedElements(), "Class7");
		IClass cls0 = (IClass)getElement(project.getOwnedElements(), "Class0");
        IGeneralization[] generalizations = cls7.getGeneralizations();  // 5-7
		try {
    		TransactionManager.beginTransaction();
    		generalizations[0].setSubType(cls0); //4-5, 0-4, 5-0
            TransactionManager.endTransaction();
            fail();
    	} catch (InvalidEditingException e) {
    		TransactionManager.abortTransaction();
    		assertEquals(e.getKey(), InvalidEditingException.CLASSIFIER_LOOP_KEY);
        }
	}

	public void testSetSuperTypeToGeneralizationExsited() throws ClassNotFoundException {
		IClass cls5 = (IClass)getElement(project.getOwnedElements(), "Class5");
		IClass cls4 = (IClass)getElement(project.getOwnedElements(), "Class4");
        IGeneralization[] generalizations = cls5.getGeneralizations();  // 0-4
		try {
    		TransactionManager.beginTransaction();
    		generalizations[0].setSubType(cls5); // 0-5
    		generalizations[0].setSuperType(cls4); //4-5, 4-5
            TransactionManager.endTransaction();
            fail();
    	} catch (InvalidEditingException e) {
    		TransactionManager.abortTransaction();
    		assertEquals(e.getKey(), InvalidEditingException.GENERALIZATION_EXIST_KEY);
        }
	}

	public void testSetSubTypeToGeneralizationExsited() throws ClassNotFoundException {
		IClass cls6 = (IClass)getElement(project.getOwnedElements(), "Class6");
		IClass cls7 = (IClass)getElement(project.getOwnedElements(), "Class7");
        IGeneralization[] generalizations = cls6.getGeneralizations();  // 5-6
		try {
    		TransactionManager.beginTransaction();
    		generalizations[0].setSubType(cls7); //5-7, 5-7
            TransactionManager.endTransaction();
            fail();
    	} catch (InvalidEditingException e) {
    		TransactionManager.abortTransaction();
    		assertEquals(e.getKey(), InvalidEditingException.GENERALIZATION_EXIST_KEY);
        }
	}
}

package com.change_vision.jude.api.test.model;

import junit.framework.Test;

import com.change_vision.jude.api.inf.editor.TransactionManager;
import com.change_vision.jude.api.inf.exception.InvalidEditingException;
import com.change_vision.jude.api.inf.model.IClass;
import com.change_vision.jude.api.inf.model.IClassifierTemplateParameter;
import com.change_vision.jude.api.inf.model.ITemplateBinding;

public class IClassifierTemplateParameterTest extends ITestCase {
    public static Test suite() {
        return suite("testModel/judeAPITest/IClassifierTemplateParameterTest.jude", IClassifierTemplateParameterTest.class);
    }

    public void testAllowSubstitutable() {
        IClass cls = (IClass)getElement(project.getOwnedElements(), "Class0");
        IClassifierTemplateParameter iParameter=
        	(IClassifierTemplateParameter) getElement(cls.getTemplateParameters(), "parameter0");
        assertTrue(iParameter.allowSubstitutable());
    }

    public void testGetType() {
        IClass cls = (IClass)getElement(project.getOwnedElements(), "Class0");
        IClassifierTemplateParameter iParameter=
        	(IClassifierTemplateParameter) getElement(cls.getTemplateParameters(), "parameter1");
        assertEquals(iParameter.getType().getName(), "int");
    }

    public void testGetDefaultValue() {
        IClass cls = (IClass)getElement(project.getOwnedElements(), "Class0");
        IClassifierTemplateParameter iParameter=
        	(IClassifierTemplateParameter) getElement(cls.getTemplateParameters(), "parameter1");
        assertTrue(iParameter.getDefaultValue().toString().equals("5"));
    }

//    public void testSetAllowSubstitutable() throws ClassNotFoundException {
//        IClass cls = (IClass)getElement(project.getOwnedElements(), "Class0");
//        IClassifierTemplateParameter iParameter=
//        	(IClassifierTemplateParameter) getElement(cls.getTemplateParameters(), "parameter0");
//        try {
//        	TransactionManager.beginTransaction();
//        	iParameter.setAllowSubstitutable(false);
//        	TransactionManager.endTransaction();
//        	assertFalse(iParameter.allowSubstitutable());
//        } catch (InvalidEditingException e) {
//			TransactionManager.abortTransaction();
//			fail();
//		}
//        try {
//        	TransactionManager.beginTransaction();
//        	iParameter.setAllowSubstitutable(true);
//        	TransactionManager.endTransaction();
//        	assertTrue(iParameter.allowSubstitutable());
//        } catch (InvalidEditingException e) {
//			TransactionManager.abortTransaction();
//			fail();
//		}
//    }

    public void testSetTypeWithSubSystem() throws ClassNotFoundException {
        IClass cls0 = (IClass)getElement(project.getOwnedElements(), "Class0");
        IClass subSystem = (IClass)getElement(project.getOwnedElements(), "Subsystem0");
        IClassifierTemplateParameter iParameter=
        	(IClassifierTemplateParameter) getElement(cls0.getTemplateParameters(), "parameter0");
        try {
        	TransactionManager.beginTransaction();
        	iParameter.setType(subSystem);
        	TransactionManager.endTransaction();
        	fail();
        } catch (InvalidEditingException e) {
			TransactionManager.abortTransaction();
			assertNull(iParameter.getType());
			assertEquals(e.getKey(), InvalidEditingException.FORBID_SUBSYSTEM_KEY);
		}
    }

    public void testSetType() throws ClassNotFoundException {
        IClass cls0 = (IClass)getElement(project.getOwnedElements(), "Class0");
        IClass cls2 = (IClass)getElement(project.getOwnedElements(), "Class2");
        IClassifierTemplateParameter iParameter=
        	(IClassifierTemplateParameter) getElement(cls0.getTemplateParameters(), "parameter0");
        try {
        	TransactionManager.beginTransaction();
        	iParameter.setType(cls2);
        	TransactionManager.endTransaction();
        	assertTrue(iParameter.getType() == cls2);
        } catch (InvalidEditingException e) {
			TransactionManager.abortTransaction();
			fail();
		}
    }

    public void testSetTypeNull() throws ClassNotFoundException {
        IClass cls0 = (IClass)getElement(project.getOwnedElements(), "Class0");
        IClassifierTemplateParameter iParameter=
        	(IClassifierTemplateParameter) getElement(cls0.getTemplateParameters(), "parameter0");
        try {
        	TransactionManager.beginTransaction();
        	iParameter.setType(null);
        	TransactionManager.endTransaction();
        	assertNull(iParameter.getType());
        } catch (InvalidEditingException e) {
			TransactionManager.abortTransaction();
			fail();
		}
    }

    public void testSetTypeExpressionWithSubSystem() throws ClassNotFoundException {
        IClass cls0 = (IClass)getElement(project.getOwnedElements(), "Class0");
        IClassifierTemplateParameter iParameter=
        	(IClassifierTemplateParameter) getElement(cls0.getTemplateParameters(), "parameter0");
        try {
        	TransactionManager.beginTransaction();
        	iParameter.setTypeExpression("Subsystem0");
        	TransactionManager.endTransaction();
        	fail();
        } catch (InvalidEditingException e) {
			TransactionManager.abortTransaction();
			assertNull(iParameter.getType());
			assertEquals(e.getKey(), InvalidEditingException.FORBID_SUBSYSTEM_KEY);
		}
    }

    public void testSetTypeExpressionWithClassNotDefined() throws ClassNotFoundException {
        IClass cls0 = (IClass)getElement(project.getOwnedElements(), "Class0");
        IClassifierTemplateParameter iParameter=
        	(IClassifierTemplateParameter) getElement(cls0.getTemplateParameters(), "parameter0");
        try {
        	TransactionManager.beginTransaction();
        	iParameter.setTypeExpression("Class100");
        	TransactionManager.endTransaction();
        	fail();
        } catch (InvalidEditingException e) {
			TransactionManager.abortTransaction();
			assertNull(iParameter.getType());
			assertEquals(e.getKey(), InvalidEditingException.NO_TARGET_CLASSIFIER_KEY);
		}
    }

    public void testSetTypeExpression() throws ClassNotFoundException {
        IClass cls0 = (IClass)getElement(project.getOwnedElements(), "Class0");
        IClass cls2 = (IClass)getElement(project.getOwnedElements(), "Class2");
        IClassifierTemplateParameter iParameter=
        	(IClassifierTemplateParameter) getElement(cls0.getTemplateParameters(), "parameter0");
        try {
        	TransactionManager.beginTransaction();
        	iParameter.setTypeExpression("Class2");
        	TransactionManager.endTransaction();
        	assertTrue(iParameter.getType() == cls2);
        } catch (InvalidEditingException e) {
			TransactionManager.abortTransaction();
			fail();
		}
    }

    public void testSetTypeExpressionNull() throws ClassNotFoundException {
        IClass cls0 = (IClass)getElement(project.getOwnedElements(), "Class0");
        IClassifierTemplateParameter iParameter=
        	(IClassifierTemplateParameter) getElement(cls0.getTemplateParameters(), "parameter0");
        try {
        	TransactionManager.beginTransaction();
        	iParameter.setTypeExpression(null);
        	TransactionManager.endTransaction();
        	assertNull(iParameter.getType());
        } catch (InvalidEditingException e) {
			TransactionManager.abortTransaction();
			fail();
		}
    }

    public void testSetDefaultValueWithString() throws ClassNotFoundException {
        IClass cls0 = (IClass)getElement(project.getOwnedElements(), "Class0");
        IClassifierTemplateParameter iParameter=
        	(IClassifierTemplateParameter) getElement(cls0.getTemplateParameters(), "parameter0");
        assertNull(iParameter.getType());
        try {
        	TransactionManager.beginTransaction();
        	iParameter.setDefaultValue("Subsystem0");
        	TransactionManager.endTransaction();
        	fail();
        } catch (InvalidEditingException e) {
			TransactionManager.abortTransaction();
			assertEquals(e.getKey(), InvalidEditingException.FORBID_SUBSYSTEM_KEY);
		}
        try {
        	TransactionManager.beginTransaction();
        	iParameter.setDefaultValue("Class100");
        	TransactionManager.endTransaction();
        	fail();
        } catch (InvalidEditingException e) {
			TransactionManager.abortTransaction();
			assertEquals(e.getKey(), InvalidEditingException.NO_TARGET_CLASSIFIER_KEY);
		}
        IClass cls1 = (IClass)getElement(project.getOwnedElements(), "Class1");
        try {
        	TransactionManager.beginTransaction();
        	iParameter.setDefaultValue("Class1");
        	TransactionManager.endTransaction();
        	assertTrue(iParameter.getDefaultValue() == cls1);
        } catch (InvalidEditingException e) {
			TransactionManager.abortTransaction();
			fail();
		}
        try {
        	TransactionManager.beginTransaction();
        	iParameter.setDefaultValue(null);
        	TransactionManager.endTransaction();
        	assertNull(iParameter.getDefaultValue());
        } catch (InvalidEditingException e) {
			TransactionManager.abortTransaction();
			fail();
		}
    }

    public void testSetDefaultValueWithPrimitiveType() throws ClassNotFoundException {
        IClass cls0 = (IClass)getElement(project.getOwnedElements(), "Class0");
        IClass cls1 = (IClass)getElement(project.getOwnedElements(), "Class1");
        IClassifierTemplateParameter iParameter=
        	(IClassifierTemplateParameter) getElement(cls0.getTemplateParameters(), "parameter1");
        assertEquals(iParameter.getType().getName(), "int");
        try {
        	TransactionManager.beginTransaction();
        	iParameter.setDefaultValue(cls1);
        	TransactionManager.endTransaction();
        	fail();
        } catch (InvalidEditingException e) {
			TransactionManager.abortTransaction();
			assertEquals(e.getKey(), InvalidEditingException.TEMPLATE_PARAM_DEFAULT_VALUE_ERROR_KEY);
		}
        try {
        	TransactionManager.beginTransaction();
        	iParameter.setDefaultValue("100");
        	TransactionManager.endTransaction();
        	assertEquals("100", iParameter.getDefaultValue().toString());
        } catch (InvalidEditingException e) {
			TransactionManager.abortTransaction();
			fail();
		}
        try {
        	TransactionManager.beginTransaction();
        	iParameter.setDefaultValue(null);
        	TransactionManager.endTransaction();
        	assertNull(iParameter.getDefaultValue());
        } catch (InvalidEditingException e) {
			TransactionManager.abortTransaction();
			fail();
		}
    }

    public void testSetDefaultValueWithClassType() throws ClassNotFoundException {
        IClass cls0 = (IClass)getElement(project.getOwnedElements(), "Class0");
        IClass cls5 = (IClass)getElement(project.getOwnedElements(), "Class5");
        IClass cls6 = (IClass)getElement(project.getOwnedElements(), "Class6");
        IClass cls7 = (IClass)getElement(project.getOwnedElements(), "Class7");
        IClassifierTemplateParameter iParameter=
        	(IClassifierTemplateParameter) getElement(cls0.getTemplateParameters(), "parameter0");
        try {
        	TransactionManager.beginTransaction();
        	iParameter.setTypeExpression("Class4");
        	iParameter.setDefaultValue(cls5);
        	TransactionManager.endTransaction();
        	fail();
        } catch (InvalidEditingException e) {
			TransactionManager.abortTransaction();
			assertEquals(e.getKey(), InvalidEditingException.MUST_SUB_CLASS_ERROR_KEY);
		}
        try {
        	TransactionManager.beginTransaction();
        	iParameter.setTypeExpression("Class4");
        	iParameter.setDefaultValue(cls7);
        	TransactionManager.endTransaction();
        	fail();
        } catch (InvalidEditingException e) {
			TransactionManager.abortTransaction();
			assertEquals(e.getKey(), InvalidEditingException.MUST_SUB_CLASS_ERROR_KEY);
		}
        try {
        	TransactionManager.beginTransaction();
        	iParameter.setTypeExpression("Class4");
        	iParameter.setDefaultValue("Class100");
        	TransactionManager.endTransaction();
        	fail();
        } catch (InvalidEditingException e) {
			TransactionManager.abortTransaction();
			assertEquals(e.getKey(), InvalidEditingException.NO_TARGET_CLASSIFIER_KEY);
		}
        try {
        	TransactionManager.beginTransaction();
        	iParameter.setTypeExpression("Class4");
        	iParameter.setDefaultValue(cls6);
        	TransactionManager.endTransaction();
        	assertTrue(cls6 == iParameter.getDefaultValue());
        } catch (InvalidEditingException e) {
			TransactionManager.abortTransaction();
			fail();
		}
        try {
        	TransactionManager.beginTransaction();
        	iParameter.setDefaultValue(null);
        	TransactionManager.endTransaction();
        	assertNull(iParameter.getDefaultValue());
        } catch (InvalidEditingException e) {
			TransactionManager.abortTransaction();
			fail();
		}
    }

    public void testChangeType() throws ClassNotFoundException {
        IClass cls0 = (IClass)getElement(project.getOwnedElements(), "Class0");
        IClass cls1 = (IClass)getElement(project.getOwnedElements(), "Class1");
        IClassifierTemplateParameter iParameter=
        	(IClassifierTemplateParameter) getElement(cls0.getTemplateParameters(), "parameter1");
        ITemplateBinding binding = cls0.getTemplateBindings()[0];
        assertNotNull(binding.getActualMap());
        assertTrue(binding.getActualMap().size() == 1);
        assertNotNull(binding.getActualMap().get(iParameter));
        try {
        	TransactionManager.beginTransaction();
        	iParameter.setTypeExpression("Class1");
        	TransactionManager.endTransaction();
        	assertTrue(iParameter.getType() == cls1);
        	assertNull(iParameter.getDefaultValue());
        	assertNull(binding.getActualMap().get(iParameter));
        	assertTrue(binding.getActualMap().size() == 0);
        } catch (InvalidEditingException e) {
			TransactionManager.abortTransaction();
			fail();
		}
    }
}

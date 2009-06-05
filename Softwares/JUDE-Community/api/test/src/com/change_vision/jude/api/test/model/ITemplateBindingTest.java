package com.change_vision.jude.api.test.model;

import junit.framework.Test;

import com.change_vision.jude.api.inf.editor.TransactionManager;
import com.change_vision.jude.api.inf.exception.InvalidEditingException;
import com.change_vision.jude.api.inf.model.IClass;
import com.change_vision.jude.api.inf.model.IClassifierTemplateParameter;
import com.change_vision.jude.api.inf.model.ITemplateBinding;

public class ITemplateBindingTest extends ITestCase {

	public static Test suite() {
        return suite("testModel/judeAPITest/IClassifierTemplateParameterTest.jude", ITemplateBindingTest.class);
    }

	public void testGetBoundElement() {
        IClass cls0 = (IClass)getElement(project.getOwnedElements(), "Class0");
        IClass cls4 = (IClass)getElement(project.getOwnedElements(), "Class4");
        ITemplateBinding[] bindings = cls0.getTemplateBindings();
        assertTrue(bindings.length == 1);
        assertEquals(cls4, bindings[0].getBoundElement());
    }

	public void testGetTemplate() {
        IClass cls0 = (IClass)getElement(project.getOwnedElements(), "Class0");
        ITemplateBinding[] bindings = cls0.getTemplateBindings();
        assertTrue(bindings.length == 1);
        assertEquals(cls0, bindings[0].getTemplate());
    }

	public void testGetActualMap() {
        IClass cls0 = (IClass)getElement(project.getOwnedElements(), "Class0");
        IClassifierTemplateParameter iParameter=
        	(IClassifierTemplateParameter) getElement(cls0.getTemplateParameters(), "parameter1");
        ITemplateBinding[] bindings = cls0.getTemplateBindings();
        assertTrue(bindings.length == 1);
        assertTrue(bindings[0].getActualMap().size() == 1);
        assertNotNull(bindings[0].getActualMap().get(iParameter));
        assertEquals(bindings[0].getActualMap().get(iParameter).toString(), "10");
    }

	public void testAddActualParameterWithInvalidParameter() throws ClassNotFoundException {
		IClass cls0 = (IClass)getElement(project.getOwnedElements(), "Class0");
        ITemplateBinding[] bindings = cls0.getTemplateBindings();
        try {
        	TransactionManager.beginTransaction();
        	bindings[0].addActualParameter(null, "Class1");
        	TransactionManager.endTransaction();
        	fail();
        } catch (InvalidEditingException e) {
			TransactionManager.abortTransaction();
			assertEquals(e.getKey(), InvalidEditingException.PARAMETER_ERROR_KEY);
		}

        IClass cls5 = (IClass)getElement(project.getOwnedElements(), "Class5");
		IClassifierTemplateParameter iParameter=
        	(IClassifierTemplateParameter) getElement(cls5.getTemplateParameters(), "parameter3");
		assertNotNull(iParameter);
        try {
        	TransactionManager.beginTransaction();
        	bindings[0].addActualParameter(iParameter, "Class1");
        	TransactionManager.endTransaction();
        	fail();
        } catch (InvalidEditingException e) {
			TransactionManager.abortTransaction();
			assertEquals(e.getKey(), InvalidEditingException.INVALID_PARAMETER_KEY);
		}
	}

	public void testAddActualParameterWithString() throws ClassNotFoundException {
        IClass cls0 = (IClass)getElement(project.getOwnedElements(), "Class0");
        ITemplateBinding[] bindings = cls0.getTemplateBindings();
        assertTrue(bindings.length == 1);
        IClassifierTemplateParameter iParameter=
        	(IClassifierTemplateParameter) getElement(cls0.getTemplateParameters(), "parameter0");
        assertNull(iParameter.getType());
        try {
        	TransactionManager.beginTransaction();
        	bindings[0].addActualParameter(iParameter, "Subsystem0");
        	TransactionManager.endTransaction();
        	fail();
        } catch (InvalidEditingException e) {
			TransactionManager.abortTransaction();
			assertEquals(e.getKey(), InvalidEditingException.FORBID_SUBSYSTEM_KEY);
		}
        try {
        	TransactionManager.beginTransaction();
        	bindings[0].addActualParameter(iParameter, "Class100");
        	TransactionManager.endTransaction();
        	fail();
        } catch (InvalidEditingException e) {
			TransactionManager.abortTransaction();
			assertEquals(e.getKey(), InvalidEditingException.NO_TARGET_CLASSIFIER_KEY);
		}
        IClass cls1 = (IClass)getElement(project.getOwnedElements(), "Class1");
        try {
        	TransactionManager.beginTransaction();
        	bindings[0].addActualParameter(iParameter, "Class1");
        	TransactionManager.endTransaction();
        	assertTrue(bindings[0].getActualMap().size() == 2);
        	assertTrue(bindings[0].getActualMap().get(iParameter) == cls1);
        } catch (InvalidEditingException e) {
			TransactionManager.abortTransaction();
			fail();
		}
        try {
        	TransactionManager.beginTransaction();
        	bindings[0].addActualParameter(iParameter, null);
        	TransactionManager.endTransaction();
        	assertTrue(bindings[0].getActualMap().size() == 1);
        	assertNull(bindings[0].getActualMap().get(iParameter));
        } catch (InvalidEditingException e) {
			TransactionManager.abortTransaction();
			fail();
		}
    }

    public void testAddActualParameterWithPrimitiveType() throws ClassNotFoundException {
        IClass cls0 = (IClass)getElement(project.getOwnedElements(), "Class0");
        ITemplateBinding[] bindings = cls0.getTemplateBindings();
        assertTrue(bindings.length == 1);
        IClassifierTemplateParameter iParameter=
        	(IClassifierTemplateParameter) getElement(cls0.getTemplateParameters(), "parameter1");
        assertEquals(iParameter.getType().getName(), "int");
        IClass cls1 = (IClass)getElement(project.getOwnedElements(), "Class1");
        try {
        	TransactionManager.beginTransaction();
        	bindings[0].addActualParameter(iParameter, cls1);
        	TransactionManager.endTransaction();
        	fail();
        } catch (InvalidEditingException e) {
			TransactionManager.abortTransaction();
			assertEquals(e.getKey(), InvalidEditingException.TEMPLATE_PARAM_ACTUAL_VALUE_ERROR_KEY);
		}
        try {
        	TransactionManager.beginTransaction();
        	bindings[0].addActualParameter(iParameter, "100");
        	TransactionManager.endTransaction();
        	assertEquals("100", bindings[0].getActualMap().get(iParameter).toString());
        } catch (InvalidEditingException e) {
			TransactionManager.abortTransaction();
			fail();
		}
    }

    public void testAddActualParameterWithClassType() throws ClassNotFoundException {
        IClass cls0 = (IClass)getElement(project.getOwnedElements(), "Class0");
        IClass cls5 = (IClass)getElement(project.getOwnedElements(), "Class5");
        IClass cls6 = (IClass)getElement(project.getOwnedElements(), "Class6");
        IClass cls7 = (IClass)getElement(project.getOwnedElements(), "Class7");

        ITemplateBinding[] bindings = cls0.getTemplateBindings();
        assertTrue(bindings.length == 1);
        IClassifierTemplateParameter iParameter =
        	(IClassifierTemplateParameter) getElement(cls0.getTemplateParameters(), "parameter0");
        try {
        	TransactionManager.beginTransaction();
        	iParameter.setTypeExpression("Class4");
        	bindings[0].addActualParameter(iParameter, cls5);
        	TransactionManager.endTransaction();
        	fail();
        } catch (InvalidEditingException e) {
			TransactionManager.abortTransaction();
			assertEquals(e.getKey(), InvalidEditingException.MUST_SUB_CLASS_ERROR_KEY);
		}
        try {
        	TransactionManager.beginTransaction();
        	iParameter.setTypeExpression("Class4");
        	bindings[0].addActualParameter(iParameter, cls7);
        	TransactionManager.endTransaction();
        	fail();
        } catch (InvalidEditingException e) {
			TransactionManager.abortTransaction();
			assertEquals(e.getKey(), InvalidEditingException.MUST_SUB_CLASS_ERROR_KEY);
		}
        try {
        	TransactionManager.beginTransaction();
        	iParameter.setTypeExpression("Class4");
        	bindings[0].addActualParameter(iParameter, "Class100");
        	TransactionManager.endTransaction();
        	fail();
        } catch (InvalidEditingException e) {
			TransactionManager.abortTransaction();
			assertEquals(e.getKey(), InvalidEditingException.NO_TARGET_CLASSIFIER_KEY);
		}
        try {
        	TransactionManager.beginTransaction();
        	iParameter.setTypeExpression("Class4");
        	bindings[0].addActualParameter(iParameter, cls6);
        	TransactionManager.endTransaction();
        	assertTrue(cls6 == bindings[0].getActualMap().get(iParameter));
        } catch (InvalidEditingException e) {
			TransactionManager.abortTransaction();
			fail();
		}
        try {
        	TransactionManager.beginTransaction();
        	bindings[0].addActualParameter(iParameter, null);
        	TransactionManager.endTransaction();
        	assertNull(bindings[0].getActualMap().get(iParameter));
        } catch (InvalidEditingException e) {
			TransactionManager.abortTransaction();
			fail();
		}
        //anonymousBoundClass: loop
        IClass cls4 = (IClass)getElement(project.getOwnedElements(), "Class4");
        bindings = cls4.getTemplateBindings(); //4-0, class4<?>-4
        assertTrue(bindings.length == 2);
        IClass anonymousClass = bindings[1].getBoundElement();
        iParameter =
        	(IClassifierTemplateParameter) getElement(cls4.getTemplateParameters(), "parameter2");
        try {
        	TransactionManager.beginTransaction();
        	bindings[1].addActualParameter(iParameter, anonymousClass);
        	TransactionManager.endTransaction();
        	fail();
        } catch (InvalidEditingException e) {
			TransactionManager.abortTransaction();
			assertEquals(e.getKey(), InvalidEditingException.ANONYMOUS_BOUND_CLASS_LOOP_KEY);
		}
    }

    public void testRemoveActualParameterWithClassType() throws ClassNotFoundException {
    	IClass cls0 = (IClass)getElement(project.getOwnedElements(), "Class0");
        ITemplateBinding[] bindings = cls0.getTemplateBindings();
        assertTrue(bindings.length == 1);
        IClassifierTemplateParameter iParameter =
        	(IClassifierTemplateParameter) getElement(cls0.getTemplateParameters(), "parameter1");
        assertTrue(bindings[0].getActualMap().size() == 1);
        assertNotNull(bindings[0].getActualMap().get(iParameter));
        try {
        	TransactionManager.beginTransaction();
        	bindings[0].removeActualParameter(iParameter);
        	TransactionManager.endTransaction();
        	assertTrue(bindings[0].getActualMap().size() == 0);
        	assertNull(bindings[0].getActualMap().get(iParameter));
        } catch (InvalidEditingException e) {
			TransactionManager.abortTransaction();
			fail();
		}
    }
}

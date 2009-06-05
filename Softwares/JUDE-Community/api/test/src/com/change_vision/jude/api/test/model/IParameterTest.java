package com.change_vision.jude.api.test.model;

import junit.framework.Test;

import com.change_vision.jude.api.inf.editor.BasicModelEditor;
import com.change_vision.jude.api.inf.editor.ModelEditorFactory;
import com.change_vision.jude.api.inf.editor.TransactionManager;
import com.change_vision.jude.api.inf.exception.InvalidEditingException;
import com.change_vision.jude.api.inf.model.IClass;
import com.change_vision.jude.api.inf.model.IOperation;
import com.change_vision.jude.api.inf.model.IParameter;

public class IParameterTest extends ITestCase {

    public static Test suite() {
        return suite("testModel/judeAPITest/IOperationTest.jude", IParameterTest.class);
    }

    public void testGetType_Class1_ARRAY() {
        IClass cls = (IClass)getElement(project.getOwnedElements(), "Class0");
        IOperation op = (IOperation)getElement(cls.getOperations(), "operation3");
        IParameter param = (IParameter)getElement(op.getParameters(), "param0");
        assertEquals("Class1", param.getType().getName());
        assertEquals("Class1[]", param.getTypeExpression());
	}

    public void testGetType_int() {
        IClass cls = (IClass)getElement(project.getOwnedElements(), "Class0");
        IOperation op = (IOperation)getElement(cls.getOperations(), "operation3");
        IParameter param = (IParameter)getElement(op.getParameters(), "param1");
        assertEquals("int", param.getType().getName());
        assertEquals("int", param.getTypeExpression());
    }

    public void testSetType_Null() throws ClassNotFoundException{
    	IClass cls = (IClass)getElement(project.getOwnedElements(), "Class0");
        IOperation op = (IOperation)getElement(cls.getOperations(), "operation3");
        IParameter param = (IParameter)getElement(op.getParameters(), "param1");
        assertEquals("int", param.getType().getName());
        try {
        	TransactionManager.beginTransaction();
        	param.setType(null);
        	TransactionManager.endTransaction();
        	assertNull(param.getType());
        } catch (InvalidEditingException e) {
			TransactionManager.abortTransaction();
			fail();
		}
    }

    public void testSetType() throws ClassNotFoundException{
    	IClass cls0 = (IClass)getElement(project.getOwnedElements(), "Class0");
    	IClass cls1 = (IClass)getElement(project.getOwnedElements(), "Class1");
        IOperation op = (IOperation)getElement(cls0.getOperations(), "operation3");
        IParameter param = (IParameter)getElement(op.getParameters(), "param1");
        assertNull(param.getType());
        try {
        	TransactionManager.beginTransaction();
        	param.setType(cls1);
        	TransactionManager.endTransaction();
        	assertNotNull(param.getType());
        	assertEquals(cls1, param.getType());
        } catch (InvalidEditingException e) {
			TransactionManager.abortTransaction();
			fail();
		}
    }

    public void testsetDirectionWithNullParameter() throws ClassNotFoundException{
    	IClass cls0 = (IClass)getElement(project.getOwnedElements(), "Class0");
        IOperation op = (IOperation)getElement(cls0.getOperations(), "operation3");
        IParameter param = (IParameter)getElement(op.getParameters(), "param1");
        try {
        	TransactionManager.beginTransaction();
        	param.setDirection(null);
        	TransactionManager.endTransaction();
        	fail();
        } catch (InvalidEditingException e) {
			TransactionManager.abortTransaction();
			assertEquals(e.getKey(), InvalidEditingException.INVALID_DIRECTION_KEY);
		}
    }

    public void testsetDirectionIllegal() throws ClassNotFoundException{
    	IClass cls0 = (IClass)getElement(project.getOwnedElements(), "Class0");
        IOperation op = (IOperation)getElement(cls0.getOperations(), "operation3");
        IParameter param = (IParameter)getElement(op.getParameters(), "param1");
        try {
        	TransactionManager.beginTransaction();
        	param.setDirection("Custom");
        	TransactionManager.endTransaction();
        	fail();
        } catch (InvalidEditingException e) {
			TransactionManager.abortTransaction();
			assertEquals(e.getKey(), InvalidEditingException.INVALID_DIRECTION_KEY);
		}
    }

    public void testGetDirection(){
    	IClass cls1 = (IClass)getElement(project.getOwnedElements(), "Class1");
        IOperation op = (IOperation)getElement(cls1.getOperations(), "operation0");
        IParameter inParam = (IParameter)getElement(op.getParameters(), "inParam");
        assertEquals("in", inParam.getDirection());

        IParameter outParam = (IParameter)getElement(op.getParameters(), "outParam");
        assertEquals("out", outParam.getDirection());

        IParameter inoutParam = (IParameter)getElement(op.getParameters(), "inOutParam");
        assertEquals("inout", inoutParam.getDirection());
    }

    public void testSetDirection() throws ClassNotFoundException, Exception{
    	IClass cls1 = (IClass)getElement(project.getOwnedElements(), "Class1");
        IOperation op = (IOperation)getElement(cls1.getOperations(), "operation0");
        BasicModelEditor bme = ModelEditorFactory.getBasicModelEditor();
        try {
        	TransactionManager.beginTransaction();

        	IParameter targetParam = (IParameter)getElement(op.getParameters(), "targetParam");
        	if (targetParam == null) {
              targetParam = bme.createParameter(op, "targetParam", "int");
        	}

            assertNotNull(targetParam);

        	targetParam.setDirection("in");
        	assertNotNull(targetParam.getDirection());
        	assertEquals("in", targetParam.getDirection());

        	targetParam.setDirection("out");
        	assertNotNull(targetParam.getDirection());
        	assertEquals("out", targetParam.getDirection());

        	targetParam.setDirection("inout");
        	assertNotNull(targetParam.getDirection());
        	assertEquals("inout", targetParam.getDirection());

        	TransactionManager.endTransaction();
        } catch (InvalidEditingException e) {
			TransactionManager.abortTransaction();
			fail();
		}
    }
}

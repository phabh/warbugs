package com.change_vision.jude.api.test.model;

import junit.framework.Test;

import com.change_vision.jude.api.inf.editor.TransactionManager;
import com.change_vision.jude.api.inf.exception.InvalidEditingException;
import com.change_vision.jude.api.inf.model.IElement;
import com.change_vision.jude.api.inf.model.ITaggedValue;



public class ITaggedValueTest extends ITestCase {

    public static Test suite() {
        return suite("testModel/judeAPITest/IElementTest.jude", ITaggedValueTest.class);
    }

    public void testGetKey() {
        IElement element = getElement(project.getOwnedElements(), "UseCase0");
        ITaggedValue[] taggedValues = element.getTaggedValues();
        assertEquals("uc.description.summary", taggedValues[0].getKey());
        assertEquals("uc.description.precondition", taggedValues[1].getKey());
        assertEquals("uc.description.postcondition", taggedValues[2].getKey());
    }

    public void testGetValue() {
        IElement element = getElement(project.getOwnedElements(), "UseCase0");
        ITaggedValue[] taggedValues = element.getTaggedValues();
        assertEquals("summary", taggedValues[0].getValue());
        assertEquals("pre-condition", taggedValues[1].getValue());
        assertEquals("post-condition1\npost-condition2", taggedValues[2].getValue());
    }

    public void testSetKeyWithNullParameter() throws ClassNotFoundException {
    	IElement element = getElement(project.getOwnedElements(), "UseCase0");
    	ITaggedValue[] taggedValues = element.getTaggedValues();
        try {
        	TransactionManager.beginTransaction();
        	taggedValues[0].setKey(null);
        	TransactionManager.endTransaction();
        	fail();
        } catch (InvalidEditingException e) {
			TransactionManager.abortTransaction();
			assertEquals(e.getKey(), InvalidEditingException.PARAMETER_ERROR_KEY);
			assertEquals("uc.description.summary", taggedValues[0].getKey());
	        assertEquals("uc.description.precondition", taggedValues[1].getKey());
	        assertEquals("uc.description.postcondition", taggedValues[2].getKey());
		}
    }

    public void testSetNoKey() throws ClassNotFoundException {
    	IElement element = getElement(project.getOwnedElements(), "UseCase0");
    	ITaggedValue[] taggedValues = element.getTaggedValues();
        try {
        	TransactionManager.beginTransaction();
        	taggedValues[0].setKey("");
        	TransactionManager.endTransaction();
        	fail();
        } catch (InvalidEditingException e) {
			TransactionManager.abortTransaction();
			assertEquals(e.getKey(), InvalidEditingException.PARAMETER_ERROR_KEY);
			assertEquals("uc.description.summary", taggedValues[0].getKey());
	        assertEquals("uc.description.precondition", taggedValues[1].getKey());
	        assertEquals("uc.description.postcondition", taggedValues[2].getKey());
		}
    }

    public void testSetKey() throws ClassNotFoundException {
    	IElement element = getElement(project.getOwnedElements(), "UseCase0");
    	ITaggedValue[] taggedValues = element.getTaggedValues();
        try {
        	TransactionManager.beginTransaction();
        	taggedValues[0].setKey("testKey");
        	TransactionManager.endTransaction();
        	assertEquals("testKey", taggedValues[0].getKey());
        	assertEquals("uc.description.precondition", taggedValues[1].getKey());
            assertEquals("uc.description.postcondition", taggedValues[2].getKey());
        } catch (InvalidEditingException e) {
			TransactionManager.abortTransaction();
			fail();
		}
    }

    public void testSetValueWithNullParameter() throws ClassNotFoundException {
    	IElement element = getElement(project.getOwnedElements(), "UseCase0");
    	ITaggedValue[] taggedValues = element.getTaggedValues();
        try {
        	TransactionManager.beginTransaction();
        	taggedValues[0].setValue(null);
        	TransactionManager.endTransaction();
        	fail();
        } catch (InvalidEditingException e) {
			TransactionManager.abortTransaction();
			assertEquals(e.getKey(), InvalidEditingException.PARAMETER_ERROR_KEY);
			assertEquals("summary", taggedValues[0].getValue());
	        assertEquals("pre-condition", taggedValues[1].getValue());
	        assertEquals("post-condition1\npost-condition2", taggedValues[2].getValue());
		}
    }

    public void testSetValue() throws ClassNotFoundException {
    	IElement element = getElement(project.getOwnedElements(), "UseCase0");
    	ITaggedValue[] taggedValues = element.getTaggedValues();
        try {
        	TransactionManager.beginTransaction();
        	taggedValues[0].setValue("testValue");
        	TransactionManager.endTransaction();
        	assertEquals("testValue", taggedValues[0].getValue());
        	assertEquals("pre-condition", taggedValues[1].getValue());
	        assertEquals("post-condition1\npost-condition2", taggedValues[2].getValue());
        } catch (InvalidEditingException e) {
			TransactionManager.abortTransaction();
			fail();
		}
    }
}

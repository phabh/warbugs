package com.change_vision.jude.api.test.model;

import junit.framework.Test;

import com.change_vision.jude.api.inf.editor.TransactionManager;
import com.change_vision.jude.api.inf.exception.InvalidEditingException;
import com.change_vision.jude.api.inf.model.IAttribute;
import com.change_vision.jude.api.inf.model.IClass;
import com.change_vision.jude.api.inf.model.IConstraint;

public class IConstraintTest extends ITestCase {

    public static Test suite() {
        return suite("testModel/judeAPITest/IElementTest.jude", IConstraintTest.class);
    }

    public void testGetConstrainedElement() {
        IClass cls = (IClass)getElement(project.getOwnedElements(), "Class1");
        IAttribute attr = (IAttribute)getElement(cls.getAttributes(), "attribute0");
        IConstraint[] consts = attr.getConstraints();
        assertEquals(attr, consts[0].getConstrainedElement()[0]);
        assertEquals(attr, consts[1].getConstrainedElement()[0]);
	}

    public void testGetSpecification() {
        IClass cls = (IClass)getElement(project.getOwnedElements(), "Class1");
        IAttribute attr = (IAttribute)getElement(cls.getAttributes(), "attribute0");
        IConstraint[] consts = attr.getConstraints();
        assertEquals("constraint1", consts[0].getSpecification());
        assertEquals("constraint2", consts[1].getSpecification());
    }

    public void testSetSpecificationNull()  throws ClassNotFoundException {
    	IClass cls = (IClass)getElement(project.getOwnedElements(), "Class1");
        IAttribute attr = (IAttribute)getElement(cls.getAttributes(), "attribute0");
        IConstraint[] consts = attr.getConstraints();
        assertEquals("constraint1", consts[0].getSpecification());
        try {
        	TransactionManager.beginTransaction();
        	consts[0].setSpecification(null);
        	TransactionManager.endTransaction();
        	fail();
        } catch (InvalidEditingException e) {
			TransactionManager.abortTransaction();
			assertEquals(e.getKey(), InvalidEditingException.PARAMETER_ERROR_KEY);
		}
    }

    public void testSetSpecification()  throws ClassNotFoundException {
    	IClass cls = (IClass)getElement(project.getOwnedElements(), "Class1");
        IAttribute attr = (IAttribute)getElement(cls.getAttributes(), "attribute0");
        IConstraint[] consts = attr.getConstraints();
        assertEquals("constraint1", consts[0].getSpecification());
        try {
        	TransactionManager.beginTransaction();
        	consts[0].setSpecification("specification");
        	TransactionManager.endTransaction();
        	assertEquals("specification", consts[0].getSpecification());
        } catch (InvalidEditingException e) {
			TransactionManager.abortTransaction();
			fail();
		}
    }
}

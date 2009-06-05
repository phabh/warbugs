package com.change_vision.jude.api.test.model;

import junit.framework.Test;
import JP.co.esm.caddies.er.util.ERUtilities;

import com.change_vision.jude.api.inf.editor.TransactionManager;
import com.change_vision.jude.api.inf.exception.InvalidEditingException;
import com.change_vision.jude.api.inf.model.IERDatatype;
import com.change_vision.jude.api.inf.model.IERModel;
import com.change_vision.jude.api.inf.model.IERSchema;

public class IERDatatypeTest extends ITestCase {
    private IERSchema schema;

    public static Test suite() {
        return suite("testModel/judeAPITest/ERAPITest.jude", IERDatatypeTest.class);
    }

    protected void setUp() {
        IERModel erModel = (IERModel)getElement(project.getOwnedElements(), "ER_Model");
        schema = erModel.getSchemata()[0];
    }

    public void testGetLengthConstraint() {
        IERDatatype datatype = getDatatype(schema.getDatatypes(), "BIT");
        assertEquals("Required", datatype.getLengthConstraint());
    }

    public void testGetPrecisionConstraint() {
        IERDatatype datatype = getDatatype(schema.getDatatypes(), "BIT");
        assertEquals("None", datatype.getPrecisionConstraint());
    }

    public void testGetDefaultLengthPrecision() {
        IERDatatype datatype = getDatatype(schema.getDatatypes(), "NUMERIC");
        assertEquals("10,5", datatype.getDefaultLengthPrecision());
    }

    public void testGetDescription() {
        IERDatatype datatype = getDatatype(schema.getDatatypes(), "NUMERIC");
        assertEquals("desc", datatype.getDescription());
    }

    private IERDatatype getDatatype(IERDatatype[] datatypes, String name){
        for(int i = 0; i < datatypes.length; i++) {
            if(name.equals(datatypes[i].getName())){
                return datatypes[i];
            }
        }
        return null;
    }

    public void testSetDescriptionERModel() throws ClassNotFoundException {
        try {
            TransactionManager.beginTransaction();
			IERDatatype dataType = schema.getDatatypes()[0];
			dataType.setDescription("Description");
			TransactionManager.endTransaction();
			assertEquals("Description", dataType.getDescription());
		} catch (InvalidEditingException e) {
			TransactionManager.abortTransaction();
			e.printStackTrace();
		}
    }

    public void testSetNullDescriptionERModel() throws ClassNotFoundException {
        try {
        	TransactionManager.beginTransaction();
			IERDatatype dataType = schema.getDatatypes()[0];
			dataType.setDescription(null);
			TransactionManager.endTransaction();
			fail();
		} catch (InvalidEditingException e) {
			TransactionManager.abortTransaction();
			assertEquals(e.getKey(), InvalidEditingException.PARAMETER_ERROR_KEY);
		}
    }

    public void testSetDefaultLengthPrecision() throws ClassNotFoundException {
        try {
        	TransactionManager.beginTransaction();
        	IERDatatype dataType = schema.getDatatypes()[0];
			dataType.setDefaultLengthPrecision("11");
			TransactionManager.endTransaction();
			assertEquals("11", dataType.getDefaultLengthPrecision());
		} catch (InvalidEditingException e) {
			TransactionManager.abortTransaction();
			e.printStackTrace();
		}
    }

    public void testSetNullDefaultLengthPrecision() throws ClassNotFoundException {
        try {
        	TransactionManager.beginTransaction();
        	IERDatatype dataType = schema.getDatatypes()[0];
			dataType.setDefaultLengthPrecision(null);
			TransactionManager.endTransaction();
			fail();
		} catch (InvalidEditingException e) {
			TransactionManager.abortTransaction();
			assertEquals(e.getKey(), InvalidEditingException.PARAMETER_ERROR_KEY);
		}
    }

    public void testSetLengthConstraint() throws ClassNotFoundException {
        try {
        	TransactionManager.beginTransaction();
        	IERDatatype dataType = schema.getDatatypes()[0];
			dataType.setLengthConstraint(ERUtilities.OPTIONAL);
			TransactionManager.endTransaction();
			assertEquals(ERUtilities.OPTIONAL, dataType.getLengthConstraint());
		} catch (InvalidEditingException e) {
			TransactionManager.abortTransaction();
			assertEquals(e.getKey(), InvalidEditingException.PARAMETER_ERROR_KEY);
		}
    }

    public void testSetLengthConstraintNull() throws ClassNotFoundException {
        try {
        	TransactionManager.beginTransaction();
        	IERDatatype dataType = schema.getDatatypes()[0];
			dataType.setLengthConstraint(null);
			TransactionManager.endTransaction();
			fail();
		} catch (InvalidEditingException e) {
			TransactionManager.abortTransaction();
			assertEquals(e.getKey(), InvalidEditingException.PARAMETER_ERROR_KEY);
		}
    }

    public void testSetIllgalLengthConstraint() throws ClassNotFoundException {
        try {
        	TransactionManager.beginTransaction();
        	IERDatatype dataType = schema.getDatatypes()[0];
			dataType.setLengthConstraint("myownConstraint");
			TransactionManager.endTransaction();
			fail();
		} catch (InvalidEditingException e) {
			TransactionManager.abortTransaction();
			assertEquals(e.getKey(), InvalidEditingException.PARAMETER_ERROR_KEY);
		}
    }

    public void testPrecisionConstraint() throws ClassNotFoundException {
        try {
        	TransactionManager.beginTransaction();
        	IERDatatype dataType = schema.getDatatypes()[0];
        	dataType.setPrecisionConstraint(ERUtilities.OPTIONAL);
			TransactionManager.endTransaction();
			assertEquals(ERUtilities.OPTIONAL, dataType.getLengthConstraint());
		} catch (InvalidEditingException e) {
			TransactionManager.abortTransaction();
			assertEquals(e.getKey(), InvalidEditingException.PARAMETER_ERROR_KEY);
		}
    }

    public void testPrecisionConstraintNull() throws ClassNotFoundException {
        try {
        	TransactionManager.beginTransaction();
        	IERDatatype dataType = schema.getDatatypes()[0];
			dataType.setLengthConstraint(null);
			TransactionManager.endTransaction();
			fail();
		} catch (InvalidEditingException e) {
			TransactionManager.abortTransaction();
			assertEquals(e.getKey(), InvalidEditingException.PARAMETER_ERROR_KEY);
		}
    }

    public void testIllgalPrecisionConstraint() throws ClassNotFoundException {
        try {
        	TransactionManager.beginTransaction();
        	IERDatatype dataType = schema.getDatatypes()[0];
			dataType.setLengthConstraint("myownConstraint");
			TransactionManager.endTransaction();
			fail();
		} catch (InvalidEditingException e) {
			TransactionManager.abortTransaction();
			assertEquals(e.getKey(), InvalidEditingException.PARAMETER_ERROR_KEY);
		}
    }
}
package com.change_vision.jude.api.test.model;

import junit.framework.Test;
import JP.co.esm.caddies.er.simpleER.SimpleEREntity;

import com.change_vision.jude.api.inf.editor.TransactionManager;
import com.change_vision.jude.api.inf.exception.InvalidEditingException;
import com.change_vision.jude.api.inf.model.IEREntity;
import com.change_vision.jude.api.inf.model.IERModel;
import com.change_vision.jude.api.inf.model.IERSchema;

public class IEREntityTest extends ITestCase {
    private IERSchema schema = null;

    public static Test suite() {
        return suite("testModel/judeAPITest/ERAPITest.jude", IEREntityTest.class);
    }

    protected void setUp() {
        IERModel erModel = (IERModel)getElement(project.getOwnedElements(), "ER_Model");
        schema = erModel.getSchemata()[0];
    }

    public void testGetLogicalName() {
        IEREntity entity = getEntity(schema.getEntities(), "Entity4");
        assertEquals("Entity4", entity.getLogicalName());
    }

    public void testGetPhysicalName() {
        IEREntity entity = getEntity(schema.getEntities(), "Entity4");
        assertEquals("p_Entity4", entity.getPhysicalName());
    }

    public void testGetType() {
        IEREntity entity = getEntity(schema.getEntities(), "Entity4");
        assertEquals(SimpleEREntity.TYPE_SUMMARY, entity.getType());
    }

    public void testGetPrimaryKeys() {
        IEREntity entity = getEntity(schema.getEntities(), "Entity4");
        assertEquals(3, entity.getPrimaryKeys().length);
    }

    public void testGetForeignKeys() {
        IEREntity entity = getEntity(schema.getEntities(), "Entity7");
        assertEquals(2, entity.getForeignKeys().length);
    }

    public void testGetNonPrimaryKeys() {
        IEREntity entity = getEntity(schema.getEntities(), "Entity7");
        assertEquals(2, entity.getNonPrimaryKeys().length);
    }

    public void testGetChildrenRelationships() {
        IEREntity entity = getEntity(schema.getEntities(), "Entity1");
        assertEquals(1, entity.getChildrenRelationships().length);
    }

    public void testGetParentRelationships() {
        IEREntity entity = getEntity(schema.getEntities(), "Entity16");
        assertEquals(2, entity.getParentRelationships().length);
    }

    public void testSetLogicalNameWithNullParameter() throws ClassNotFoundException {
    	IEREntity entity = getEntity(schema.getEntities(), "Entity13");
        try {
        	TransactionManager.beginTransaction();
        	entity.setLogicalName(null);
			TransactionManager.endTransaction();
        	fail();
		} catch (InvalidEditingException e) {
			TransactionManager.abortTransaction();
			assertEquals(e.getKey(), InvalidEditingException.PARAMETER_ERROR_KEY);
		}
    }

    public void testSetNoLogicalName() throws ClassNotFoundException {
    	IEREntity entity = getEntity(schema.getEntities(), "Entity13");
        try {
        	TransactionManager.beginTransaction();
        	entity.setLogicalName("");
			TransactionManager.endTransaction();
        	fail();
		} catch (InvalidEditingException e) {
			TransactionManager.abortTransaction();
			assertEquals(e.getKey(), InvalidEditingException.NO_NAME_ERROR_KEY);
		}
    }

    public void testSetLogicalName() throws InvalidEditingException {
    	IEREntity entity = getEntity(schema.getEntities(), "Entity13");
        try {
        	TransactionManager.beginTransaction();
            entity.setLogicalName("LogicalNameEntity13");
            TransactionManager.endTransaction();
            assertEquals("LogicalNameEntity13", entity.getLogicalName());
    	} catch (InvalidEditingException e) {
    		TransactionManager.abortTransaction();
            fail();
        }
    }

    public void testSetWithDuplicatedLogicalName() throws ClassNotFoundException {
    	IEREntity entity = getEntity(schema.getEntities(), "Entity14");
		try {
	        TransactionManager.beginTransaction();
	        entity.setLogicalName("LogicalNameEntity13");
			TransactionManager.endTransaction();
			fail();
		} catch (InvalidEditingException e) {
			TransactionManager.abortTransaction();
			assertEquals(e.getKey(), InvalidEditingException.NAME_DOUBLE_ERROR_KEY);
		}
    }

    public void testSetPhysicalNameWithNullParameter() throws ClassNotFoundException {
    	IEREntity entity = getEntity(schema.getEntities(), "Entity14");
        try {
        	TransactionManager.beginTransaction();
        	entity.setPhysicalName(null);
			TransactionManager.endTransaction();
        	assertEquals("", entity.getPhysicalName());
		} catch (InvalidEditingException e) {
			TransactionManager.abortTransaction();
			fail();
		}
    }

    public void testSetNoPhysicalName() throws ClassNotFoundException {
    	IEREntity entity = getEntity(schema.getEntities(), "Entity14");
        try {
        	TransactionManager.beginTransaction();
        	entity.setPhysicalName("");
			TransactionManager.endTransaction();
			assertEquals("", entity.getPhysicalName());
		} catch (InvalidEditingException e) {
			TransactionManager.abortTransaction();
			fail();
		}
    }
    public void testSetPhysicalName() throws ClassNotFoundException {
    	IEREntity entity = getEntity(schema.getEntities(), "Entity14");
    	try {
    		TransactionManager.beginTransaction();
            entity.setPhysicalName("PhyicalNameEntity14");
            TransactionManager.endTransaction();
            assertEquals("PhyicalNameEntity14", entity.getPhysicalName());
    	} catch (InvalidEditingException e) {
    		TransactionManager.abortTransaction();
            fail();
        }
    }

    public void testSetWithDuplicatedPhysicalName() throws ClassNotFoundException {
    	IEREntity entity = getEntity(schema.getEntities(), "Entity15");
		try {
	        TransactionManager.beginTransaction();
	        entity.setPhysicalName("PhyicalNameEntity14");
			TransactionManager.endTransaction();
			fail();
		} catch (InvalidEditingException e) {
			TransactionManager.abortTransaction();
			assertEquals(e.getKey(), InvalidEditingException.NAME_DOUBLE_ERROR_KEY);
		}
    }

    public void testSetTypeWithNullParameter() throws ClassNotFoundException {
    	IEREntity entity = getEntity(schema.getEntities(), "Entity16");
        try {
        	TransactionManager.beginTransaction();
			entity.setType(null);
			TransactionManager.endTransaction();
			fail();
		} catch (InvalidEditingException e) {
			TransactionManager.abortTransaction();
			assertEquals(e.getKey(), InvalidEditingException.PARAMETER_ERROR_KEY);
		}
    }

    public void testSetTypeWithEmpty() throws ClassNotFoundException {
    	IEREntity entity = getEntity(schema.getEntities(), "Entity16");
        try {
        	TransactionManager.beginTransaction();
			entity.setType("");
			TransactionManager.endTransaction();
			assertEquals("", entity.getType());
		} catch (InvalidEditingException e) {
			TransactionManager.abortTransaction();
			fail();
		}
    }

    public void testSetTypeWithInvalidValue() throws ClassNotFoundException {
    	IEREntity entity = getEntity(schema.getEntities(), "Entity16");
        try {
        	TransactionManager.beginTransaction();
			entity.setType("Custom_Definition");
			TransactionManager.endTransaction();
			fail();
		} catch (InvalidEditingException e) {
			TransactionManager.abortTransaction();
			assertEquals(e.getKey(), InvalidEditingException.PARAMETER_ERROR_KEY);
		}
    }

    public void testSetType() throws ClassNotFoundException{
		IEREntity entity = getEntity(schema.getEntities(), "Entity16");
        try {
        	TransactionManager.beginTransaction();
			entity.setType(SimpleEREntity.TYPE_EVENT);
			TransactionManager.endTransaction();
			assertEquals(SimpleEREntity.TYPE_EVENT, entity.getType());
		} catch (InvalidEditingException e) {
			TransactionManager.abortTransaction();
			fail();
		}
    }

    private IEREntity getEntity(IEREntity[] entities, String name){
        for(int i = 0; i < entities.length; i++) {
            if(name.equals(entities[i].getName())){
                return entities[i];
            }
        }
        return null;
    }
}

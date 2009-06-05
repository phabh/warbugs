package com.change_vision.jude.api.test.model;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.Iterator;
import java.util.List;

import junit.framework.Test;

import com.change_vision.jude.api.inf.editor.TransactionManager;
import com.change_vision.jude.api.inf.exception.InvalidEditingException;
import com.change_vision.jude.api.inf.model.IConstraint;
import com.change_vision.jude.api.inf.model.IERAttribute;
import com.change_vision.jude.api.inf.model.IERDatatype;
import com.change_vision.jude.api.inf.model.IERDomain;
import com.change_vision.jude.api.inf.model.IEREntity;
import com.change_vision.jude.api.inf.model.IERModel;
import com.change_vision.jude.api.inf.model.IERSchema;
import com.change_vision.jude.api.inf.model.IERSubtypeRelationship;
import com.change_vision.jude.api.inf.model.INamedElement;

public class IERAttributeTest extends ITestCase {
    private IERSchema schema = null;

    public static Test suite() {
        return suite("testModel/judeAPITest/ERAPITest.jude", IERAttributeTest.class);
    }

    protected void setUp() {
        IERModel erModel = (IERModel)getElement(project.getOwnedElements(), "ER_Model");
        schema = erModel.getSchemata()[0];
    }

    public void testIsPrimaryKey_true(){
        IEREntity entity = getEntity(schema.getEntities(), "Entity7");
        IERAttribute attribute = getERAttribute(entity, "Attribute0");
        assertTrue(attribute.isPrimaryKey());
    }

    public void testIsPrimaryKey_false(){
        IEREntity entity = getEntity(schema.getEntities(), "Entity7");
        IERAttribute attribute = getERAttribute(entity, "Attribute2");
        assertFalse(attribute.isPrimaryKey());
    }

    public void testIsForeignKey_true(){
        IEREntity entity = getEntity(schema.getEntities(), "Entity7");
        IERAttribute attribute = getERAttribute(entity, "Attribute0");
        assertTrue(attribute.isForeignKey());
    }

    public void testIsForeignKey_false(){
        IEREntity entity = getEntity(schema.getEntities(), "Entity7");
        IERAttribute attribute = getERAttribute(entity, "Attribute2");
        assertFalse(attribute.isForeignKey());
    }

    public void testGetReferencedPrimaryKey(){
        IEREntity entity = getEntity(schema.getEntities(), "Entity1");
        IERAttribute attribute = getERAttribute(entity, "e1_Attribute2");
        assertEquals("Attribute2", attribute.getReferencedPrimaryKey().getName());
    }

    public void testGetReferencedRelationship(){
        IEREntity entity = getEntity(schema.getEntities(), "Entity1");
        IERAttribute attribute = getERAttribute(entity, "e1_Attribute2");
        assertEquals("Identifying Relationship0", attribute.getReferencedRelationship().getName());
    }

    public void testGetReferencedSubtypeRelationships(){
        IEREntity entity = getEntity(schema.getEntities(), "Entity5");
        IERAttribute attribute = getERAttribute(entity, "Attribute0");
        IERSubtypeRelationship[] relationships = attribute.getReferencedSubtypeRelationships();
        assertTrue(contains(relationships, "Subtype0"));
        assertTrue(contains(relationships, "Subtype1"));
    }

    public void testGetReferencedForeignKeys(){
        IEREntity entity = getEntity(schema.getEntities(), "Entity0");
        IERAttribute attribute = getERAttribute(entity, "Attribute2");
        IERAttribute[] fKeys = attribute.getReferencedForeignKeys();
        assertTrue(contains(fKeys, "e1_Attribute2"));
        assertTrue(contains(fKeys, "e3_Attribute2"));
    }

    public void testGetConstraint(){
        IEREntity entity = getEntity(schema.getEntities(), "Entity4");
        IERAttribute attribute = getERAttribute(entity, "Attribute3");
        IConstraint constraint = attribute.getConstraint("DEFAULT:abc");
        String value = constraint.getSpecification();
        assertEquals("DEFAULT:abc", value);
    }

    public void testIsNotNull_true(){
        IEREntity entity = getEntity(schema.getEntities(), "Entity4");
        IERAttribute attribute = getERAttribute(entity, "p_Attribute0");
        assertTrue(attribute.isNotNull());
    }

    public void testIsNotNull_false(){
        IEREntity entity = getEntity(schema.getEntities(), "Entity4");
        IERAttribute attribute = getERAttribute(entity, "Attribute3");
        assertFalse(attribute.isNotNull());
    }

    public void testGetDefaultValue(){
        IEREntity entity = getEntity(schema.getEntities(), "Entity4");
        IERAttribute attribute = getERAttribute(entity, "Attribute3");
        String defaultValue = attribute.getDefaultValue();
        assertEquals("abc", defaultValue);
    }

    public void testGetSubTypeForeignKeyInv(){
        IEREntity entity = getEntity(schema.getEntities(), "Entity7");
        IERAttribute attribute = getERAttribute(entity, "Attribute0");
        assertEquals("Subtype0", attribute.getSubtypeForeignKeyInv().getName());
    }

    public void testGetDatatype() {
        IEREntity entity = getEntity(schema.getEntities(), "Entity0");
        IERAttribute attribute = getERAttribute(entity, "Attribute3");
        assertEquals("CHAR", attribute.getDatatype().getName());
    }

    public void testGetDomain() {
        IEREntity entity = getEntity(schema.getEntities(), "Entity0");
        IERAttribute attribute = getERAttribute(entity, "Attribute2");
        assertEquals("Domain0", attribute.getDomain().getName());
    }

    public void testGetLengthPrecision() {
        IEREntity entity = getEntity(schema.getEntities(), "Entity13");
        IERAttribute attribute = getERAttribute(entity, "Attribute0");
        assertEquals("10,3", attribute.getLengthPrecision());
    }

    public void testGetLogicalName() {
        IEREntity entity = getEntity(schema.getEntities(), "Entity0");
        IERAttribute attribute = getERAttribute(entity, "Attribute2");
        assertEquals("Attribute2", attribute.getLogicalName());
    }

    public void testGetPhysicalName() {
        IEREntity entity = getEntity(schema.getEntities(), "Entity0");
        IERAttribute attribute = getERAttribute(entity, "Attribute2");
        assertEquals("p_Attribute2", attribute.getPhysicalName());
    }

    public void testSetLogicalNameWithNullParameter() throws ClassNotFoundException {
    	IEREntity entity = getEntity(schema.getEntities(), "Entity0");
    	IERAttribute attribute = getERAttribute(entity, "Attribute2");
        try {
        	TransactionManager.beginTransaction();
        	attribute.setLogicalName(null);
			TransactionManager.endTransaction();
        	fail();
		} catch (InvalidEditingException e) {
			TransactionManager.abortTransaction();
			assertEquals(e.getKey(), InvalidEditingException.PARAMETER_ERROR_KEY);
		}
    }

    public void testSetNoLogicalName() throws ClassNotFoundException {
    	IEREntity entity = getEntity(schema.getEntities(), "Entity0");
    	IERAttribute attribute = getERAttribute(entity, "Attribute2");
        try {
        	TransactionManager.beginTransaction();
        	attribute.setLogicalName("");
			TransactionManager.endTransaction();
			fail();
		} catch (InvalidEditingException e) {
			TransactionManager.abortTransaction();
			assertEquals(e.getKey(), InvalidEditingException.NO_NAME_ERROR_KEY);
		}
    }

    public void testSetLogicalName() throws ClassNotFoundException {
    	IEREntity entity = getEntity(schema.getEntities(), "Entity0");
    	IERAttribute attribute = getERAttribute(entity, "Attribute2");
    	try {
    		TransactionManager.beginTransaction();
    		attribute.setLogicalName("LogicalNameAttribute2");
            TransactionManager.endTransaction();
            assertEquals("LogicalNameAttribute2", attribute.getLogicalName());
    	} catch (InvalidEditingException e) {
    		TransactionManager.abortTransaction();
            fail();
        }
    }

    public void testSetWithDuplicatedLogicalName() throws ClassNotFoundException {
    	IEREntity entity = getEntity(schema.getEntities(), "Entity0");
    	IERAttribute attribute = getERAttribute(entity, "Attribute3");
		try {
	        TransactionManager.beginTransaction();
	        attribute.setLogicalName("LogicalNameAttribute2");
			TransactionManager.endTransaction();
			fail();
		} catch (InvalidEditingException e) {
			TransactionManager.abortTransaction();
			assertEquals(e.getKey(), InvalidEditingException.NAME_DOUBLE_ERROR_KEY);
		}
    }

    public void testSetPhysicalNameWithNullParameter() throws ClassNotFoundException {
    	IEREntity entity = getEntity(schema.getEntities(), "Entity0");
    	IERAttribute attribute = getERAttribute(entity, "Attribute3");
        try {
        	TransactionManager.beginTransaction();
        	attribute.setPhysicalName(null);
			TransactionManager.endTransaction();
			assertEquals("", attribute.getPhysicalName());
		} catch (InvalidEditingException e) {
			TransactionManager.abortTransaction();
			fail();
		}
    }

    public void testSetNoPhysicalName() throws ClassNotFoundException {
    	IEREntity entity = getEntity(schema.getEntities(), "Entity0");
    	IERAttribute attribute = getERAttribute(entity, "Attribute3");
        try {
        	TransactionManager.beginTransaction();
        	attribute.setPhysicalName("");
			TransactionManager.endTransaction();
			assertEquals("", attribute.getPhysicalName());
		} catch (InvalidEditingException e) {
			TransactionManager.abortTransaction();
			fail();
		}
    }

    public void testSetPhysicalName() throws ClassNotFoundException {
    	IEREntity entity = getEntity(schema.getEntities(), "Entity0");
    	IERAttribute attribute = getERAttribute(entity, "Attribute3");
    	try {
    		TransactionManager.beginTransaction();
    		attribute.setPhysicalName("PhyicalNameAttribute3");
            TransactionManager.endTransaction();
            assertEquals("PhyicalNameAttribute3", attribute.getPhysicalName());
    	} catch (InvalidEditingException e) {
    		TransactionManager.abortTransaction();
            fail();
        }
    }

    public void testSetWithDuplicatedPhysicalName() throws ClassNotFoundException {
    	IEREntity entity = getEntity(schema.getEntities(), "Entity0");
    	IERAttribute attribute = getERAttribute(entity, "LogicalNameAttribute2");
		try {
	        TransactionManager.beginTransaction();
	        attribute.setPhysicalName("PhyicalNameAttribute3");
			TransactionManager.endTransaction();
			fail();
		} catch (InvalidEditingException e) {
			TransactionManager.abortTransaction();
			assertEquals(e.getKey(), InvalidEditingException.NAME_DOUBLE_ERROR_KEY);
		}
    }

    public void testSetPrimaryKey() throws ClassNotFoundException {
    	IEREntity entity = getEntity(schema.getEntities(), "Entity7");
    	IERAttribute attribute = getERAttribute(entity, "Attribute2");
    	try {
    		TransactionManager.beginTransaction();
    		attribute.setPrimaryKey(true);
            TransactionManager.endTransaction();
            assertTrue(attribute.isPrimaryKey());
    	} catch (InvalidEditingException e) {
    		TransactionManager.abortTransaction();
            fail();
        }

    	try {
    		TransactionManager.beginTransaction();
    		attribute.setPrimaryKey(false);
            TransactionManager.endTransaction();
            assertFalse(attribute.isPrimaryKey());
    	} catch (InvalidEditingException e) {
    		TransactionManager.abortTransaction();
            fail();
        }
    }

    public void testSetDomainWithNullParameter() throws ClassNotFoundException {
    	IEREntity entity = getEntity(schema.getEntities(), "Entity7");
    	IERAttribute attribute = getERAttribute(entity, "Attribute0");
        try {
        	TransactionManager.beginTransaction();
        	attribute.setDomain(null);
			TransactionManager.endTransaction();
			fail();
		} catch (InvalidEditingException e) {
			TransactionManager.abortTransaction();
			assertEquals(e.getKey(), InvalidEditingException.PARAMETER_ERROR_KEY);
		}
    }

    public void testSetDomain() throws ClassNotFoundException {
    	IEREntity entity = getEntity(schema.getEntities(), "Entity7");
    	IERAttribute attribute = getERAttribute(entity, "Attribute0");
    	IERDomain domain = schema.getDomains()[1];
    	try {
    		TransactionManager.beginTransaction();
    		attribute.setDomain(domain);
            TransactionManager.endTransaction();
            assertTrue(attribute.getDatatype() != null);
        	assertTrue(attribute.getDomain() != null);
        	assertEquals(attribute.getDomain().getName(), "Domain1");
        	assertEquals(attribute.getDomain().getDatatypeName(), "NUMERIC");
        	assertEquals(attribute.getDomain().getLengthPrecision(), "10,3");
        	assertEquals(attribute.getDomain().getDefaultValue(), "");
        	assertFalse(attribute.getDomain().isNotNull());
        	assertEquals(attribute.getDomain().getDefinition(), "");
    	} catch (InvalidEditingException e) {
    		TransactionManager.abortTransaction();
            fail();
        }
    }

    public void testSetDatatypeWithNullParameter() throws ClassNotFoundException {
    	IEREntity entity = getEntity(schema.getEntities(), "Entity7");
    	IERAttribute attribute = getERAttribute(entity, "Attribute1");
        try {
        	TransactionManager.beginTransaction();
        	attribute.setDatatype(null);
			TransactionManager.endTransaction();
			fail();
		} catch (InvalidEditingException e) {
			TransactionManager.abortTransaction();
			assertEquals(e.getKey(), InvalidEditingException.PARAMETER_ERROR_KEY);
		}
    }

    public void testSetDatatype() throws ClassNotFoundException {
    	IEREntity entity = getEntity(schema.getEntities(), "Entity7");
    	IERAttribute attribute = getERAttribute(entity, "Attribute0");
    	IERDatatype datatype = schema.getDatatypes()[5];
    	try {
    		TransactionManager.beginTransaction();
    		attribute.setDatatype(datatype);
            TransactionManager.endTransaction();
            assertTrue(attribute.getDomain() == null);
        	assertTrue(attribute.getDatatype() != null);
        	assertEquals(attribute.getDatatype().getName(), "DECIMAL");
        	assertEquals(attribute.getDatatype().getDefaultLengthPrecision(), "10");
        	assertEquals(attribute.getDatatype().getLengthConstraint(), "Optional");
        	assertEquals(attribute.getDatatype().getPrecisionConstraint(), "Required");
        	assertEquals(attribute.getDatatype().getDescription(), "");
    	} catch (InvalidEditingException e) {
    		TransactionManager.abortTransaction();
            fail();
        }
    }

    public void testSetLengthPresicionWithNullParameter() throws ClassNotFoundException {
    	IEREntity entity = getEntity(schema.getEntities(), "Entity7");
    	IERAttribute attribute = getERAttribute(entity, "Attribute0");
        try {
        	TransactionManager.beginTransaction();
        	attribute.setLengthPrecision(null);
			TransactionManager.endTransaction();
			fail();
		} catch (InvalidEditingException e) {
			TransactionManager.abortTransaction();
			assertEquals(e.getKey(), InvalidEditingException.PARAMETER_ERROR_KEY);
		}
    }

    public void testSetLengthPresicion() throws ClassNotFoundException {
    	IEREntity entity = getEntity(schema.getEntities(), "Entity7");
    	IERAttribute attribute = getERAttribute(entity, "Attribute0");
    	try {
    		TransactionManager.beginTransaction();
    		attribute.setLengthPrecision("5,5");
            TransactionManager.endTransaction();
            assertEquals(attribute.getLengthPrecision(), "5,5");
    	} catch (InvalidEditingException e) {
    		TransactionManager.abortTransaction();
            fail();
        }
    }

    public void testSetNotNull() throws ClassNotFoundException {
    	IEREntity entity = getEntity(schema.getEntities(), "Entity7");
    	IERAttribute attribute = getERAttribute(entity, "Attribute2");
    	try {
    		TransactionManager.beginTransaction();
    		attribute.setNotNull(true);
            TransactionManager.endTransaction();
            assertTrue(attribute.isNotNull());
    	} catch (InvalidEditingException e) {
    		TransactionManager.abortTransaction();
            fail();
        }

    	try {
    		TransactionManager.beginTransaction();
    		attribute.setNotNull(false);
            TransactionManager.endTransaction();
            assertFalse(attribute.isNotNull());
    	} catch (InvalidEditingException e) {
    		TransactionManager.abortTransaction();
            fail();
        }
    }

    public void testSetDefaultValueWithNullParameter() throws ClassNotFoundException {
    	IEREntity entity = getEntity(schema.getEntities(), "Entity7");
    	IERAttribute attribute = getERAttribute(entity, "Attribute0");
        try {
        	TransactionManager.beginTransaction();
        	attribute.setDefaultValue(null);
			TransactionManager.endTransaction();
			fail();
		} catch (InvalidEditingException e) {
			TransactionManager.abortTransaction();
			assertEquals(e.getKey(), InvalidEditingException.PARAMETER_ERROR_KEY);
		}
    }

    public void testSetDefaultValue(String defaultValue) throws ClassNotFoundException {
    	IEREntity entity = getEntity(schema.getEntities(), "Entity7");
    	IERAttribute attribute = getERAttribute(entity, "Attribute0");
        try {
        	TransactionManager.beginTransaction();
        	attribute.setDefaultValue("defaultvalue");
			TransactionManager.endTransaction();
			fail();
		} catch (InvalidEditingException e) {
			TransactionManager.abortTransaction();
			assertEquals(attribute.getDefaultValue(), "defaultvalue");
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

    private IERAttribute getERAttribute(IEREntity entity, String attributeName){
        List attributes = new ArrayList();
        attributes.addAll(Arrays.asList(entity.getPrimaryKeys()));
        attributes.addAll(Arrays.asList(entity.getNonPrimaryKeys()));

        return getERAttribute(attributes, attributeName);
    }

    private IERAttribute getERAttribute(List attributes, String attributeName) {
        for(Iterator iter = attributes.iterator(); iter.hasNext();){
            INamedElement attribute = (INamedElement) iter.next();
            if(attributeName.equals(attribute.getName())){
                return (IERAttribute)attribute;
            }
        }
        return null;
    }

    private boolean contains(Object[] array, String targetName){
        for(int i = 0; i < array.length; i++){
            INamedElement element = (INamedElement) array[i];
            if(targetName.equals(element.getName())){
                return true;
            }
        }
        return false;
    }
}

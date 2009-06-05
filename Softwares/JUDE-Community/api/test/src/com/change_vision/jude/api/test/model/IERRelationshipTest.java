package com.change_vision.jude.api.test.model;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.Iterator;
import java.util.List;

import junit.framework.Test;

import com.change_vision.jude.api.inf.editor.TransactionManager;
import com.change_vision.jude.api.inf.exception.InvalidEditingException;
import com.change_vision.jude.api.inf.model.IERAttribute;
import com.change_vision.jude.api.inf.model.IEREntity;
import com.change_vision.jude.api.inf.model.IERModel;
import com.change_vision.jude.api.inf.model.IERRelationship;
import com.change_vision.jude.api.inf.model.IERSchema;
import com.change_vision.jude.api.inf.model.INamedElement;

public class IERRelationshipTest extends ITestCase {
    private IERSchema schema = null;

    public static Test suite() {
        return suite("testModel/judeAPITest/IERRelationshipTest.jude", IERRelationshipTest.class);
    }

    protected void setUp() {
        IERModel erModel = (IERModel)getElement(project.getOwnedElements(), "ER_Model");
        schema = erModel.getSchemata()[0];
    }

    public void testGetLogicalName(){
        //Identifying Relationship0
        IEREntity entity = getEntity(schema.getEntities(), "Entity1");
        IERAttribute attribute = getERAttribute(entity, "e1_Attribute2");
        IERRelationship relationship = attribute.getReferencedRelationship();
        assertEquals("Identifying Relationship0", relationship.getLogicalName());
    }

    public void testGetPhysicalName(){
        //Identifying Relationship0
        IEREntity entity = getEntity(schema.getEntities(), "Entity1");
        IERAttribute attribute = getERAttribute(entity, "e1_Attribute2");
        IERRelationship relationship = attribute.getReferencedRelationship();
        assertEquals("p_Identifying Relationship0", relationship.getPhysicalName());
    }

    public void testGetVerbPhraseParent(){
        //Identifying Relationship0
        IEREntity entity = getEntity(schema.getEntities(), "Entity1");
        IERAttribute attribute = getERAttribute(entity, "e1_Attribute2");
        IERRelationship relationship = attribute.getReferencedRelationship();
        assertEquals("verbP2C", relationship.getVerbPhraseParent());
    }

    public void testGetVerbPhraseChild(){
        //Identifying Relationship0
        IEREntity entity = getEntity(schema.getEntities(), "Entity1");
        IERAttribute attribute = getERAttribute(entity, "e1_Attribute2");
        IERRelationship relationship = attribute.getReferencedRelationship();
        assertEquals("verbC2P", relationship.getVerbPhraseChild());
    }

    public void testIsParentRequired_true(){
        //Identifying Relationship1
        IEREntity entity = getEntity(schema.getEntities(), "Entity2");
        IERAttribute attribute = getERAttribute(entity, "e1_Attribute2");
        IERRelationship relationship = attribute.getReferencedRelationship();
        assertTrue(relationship.isParentRequired());
    }

    public void testIsParentRequired_false(){
        //"Non-identifying Relationship0"
        IEREntity entity = getEntity(schema.getEntities(), "Entity3");
        IERAttribute attribute = getERAttribute(entity, "e3_Attribute2");
        IERRelationship relationship = attribute.getReferencedRelationship();
        assertFalse(relationship.isParentRequired());
    }

    public void testIsIdentifying_true(){
        //Identifying Relationship1
        IEREntity entity = getEntity(schema.getEntities(), "Entity2");
        IERAttribute attribute = getERAttribute(entity, "e1_Attribute2");
        IERRelationship relationship = attribute.getReferencedRelationship();
        assertTrue(relationship.isIdentifying());
    }

    public void testIsIdentifying_false(){
        //"Non-identifying Relationship0"
        IEREntity entity = getEntity(schema.getEntities(), "Entity3");
        IERAttribute attribute = getERAttribute(entity, "e3_Attribute2");
        IERRelationship relationship = attribute.getReferencedRelationship();
        assertFalse(relationship.isIdentifying());
    }

    public void testIsNonIdentifying_true(){
        //"Non-identifying Relationship0"
        IEREntity entity = getEntity(schema.getEntities(), "Entity3");
        IERAttribute attribute = getERAttribute(entity, "e3_Attribute2");
        IERRelationship relationship = attribute.getReferencedRelationship();
        assertTrue(relationship.isNonIdentifying());
    }

    public void testIsNonIdentifying_false(){
        //Identifying Relationship1
        IEREntity entity = getEntity(schema.getEntities(), "Entity2");
        IERAttribute attribute = getERAttribute(entity, "e1_Attribute2");
        IERRelationship relationship = attribute.getReferencedRelationship();
        assertFalse(relationship.isNonIdentifying());
    }

    public void testIsMultiToMulti_true(){
        //Multi2Multi Relationship0
        IEREntity entity = getEntity(schema.getEntities(), "Entity8");
        IERRelationship[] relationships = entity.getChildrenRelationships();
        assertTrue(relationships[0].isMultiToMulti());
    }

    public void testIsMultiToMulti_false(){
        //Identifying Relationship1
        IEREntity entity = getEntity(schema.getEntities(), "Entity2");
        IERAttribute attribute = getERAttribute(entity, "e1_Attribute2");
        IERRelationship relationship = attribute.getReferencedRelationship();
        assertFalse(relationship.isMultiToMulti());
    }

    public void testGetFKs(){
        //Identifying Relationship0
        IEREntity entity = getEntity(schema.getEntities(), "Entity1");
        IERAttribute attribute = getERAttribute(entity, "e1_Attribute2");
        IERRelationship relationship = attribute.getReferencedRelationship();
        assertEquals(1, relationship.getForeignKeys().length);
    }

    public void testGetChild(){
        //Identifying Relationship1
        IEREntity entity = getEntity(schema.getEntities(), "Entity2");
        IERAttribute attribute = getERAttribute(entity, "e1_Attribute2");
        IERRelationship relationship = attribute.getReferencedRelationship();
        assertEquals("Entity2", relationship.getChild().getLogicalName());
    }

    public void testGetParent(){
        //Identifying Relationship1
        IEREntity entity = getEntity(schema.getEntities(), "Entity2");
        IERAttribute attribute = getERAttribute(entity, "e1_Attribute2");
        IERRelationship relationship = attribute.getReferencedRelationship();
        assertEquals("Entity1", relationship.getParent().getLogicalName());
    }

    private IERAttribute getERAttribute(IEREntity entity, String attributeName){
        List attributes = new ArrayList();
        attributes.addAll(Arrays.asList(entity.getPrimaryKeys()));
        attributes.addAll(Arrays.asList(entity.getNonPrimaryKeys()));

        return getERAttribute(attributes, attributeName);
    }

    private IEREntity getEntity(IEREntity[] entities, String name){
        for(int i = 0; i < entities.length; i++) {
            if(name.equals(entities[i].getName())){
                return entities[i];
            }
        }
        return null;
    }

    private IERAttribute getERAttribute(List attributes, String attributeName){
        for(Iterator iter = attributes.iterator(); iter.hasNext();){
            INamedElement attribute = (INamedElement) iter.next();
            if(attributeName.equals(attribute.getName())){
                return (IERAttribute)attribute;
            }
        }
        return null;
    }

    public void testSetNullLogicalName() {
        try {
        	TransactionManager.beginTransaction();
            IEREntity entity = getEntity(schema.getEntities(), "Entity2");
            IERAttribute attribute = getERAttribute(entity, "e1_Attribute2");
            IERRelationship relationship = attribute.getReferencedRelationship();
            relationship.setLogicalName(null);
            TransactionManager.endTransaction();
			fail();
		} catch (InvalidEditingException e) {
			TransactionManager.abortTransaction();
			assertEquals(e.getKey(), InvalidEditingException.PARAMETER_ERROR_KEY);
		}
    }

    public void testSetLogicalName() {
        try {
        	TransactionManager.beginTransaction();
            IEREntity entity = getEntity(schema.getEntities(), "Entity2");
            IERAttribute attribute = getERAttribute(entity, "e1_Attribute2");
            IERRelationship relationship = attribute.getReferencedRelationship();
			relationship.setLogicalName("relationShipLogicalName");
			TransactionManager.endTransaction();
			assertEquals(relationship.getLogicalName(), "relationShipLogicalName");
		} catch (InvalidEditingException e) {
			TransactionManager.abortTransaction();
			e.printStackTrace();
		}
    }

    public void testSetNoLogicalName() {
        try {
        	TransactionManager.beginTransaction();
            IEREntity entity = getEntity(schema.getEntities(), "Entity2");
            IERAttribute attribute = getERAttribute(entity, "e1_Attribute2");
            IERRelationship relationship = attribute.getReferencedRelationship();
			relationship.setLogicalName("");
			TransactionManager.endTransaction();
			assertEquals("", relationship.getLogicalName());
		} catch (InvalidEditingException e) {
			TransactionManager.abortTransaction();
			fail();
		}
    }

    public void testSetPhysicalName() {
        try {
        	TransactionManager.beginTransaction();
            IEREntity entity = getEntity(schema.getEntities(), "Entity2");
            IERAttribute attribute = getERAttribute(entity, "e1_Attribute2");
            IERRelationship relationship = attribute.getReferencedRelationship();
			relationship.setPhysicalName("relationShipPhysicalName");
			TransactionManager.endTransaction();
			assertEquals(relationship.getPhysicalName(), "relationShipPhysicalName");
		} catch (InvalidEditingException e) {
			TransactionManager.abortTransaction();
			fail();
		}
    }

    public void testSetNoPhysicalName() {
        try {
        	TransactionManager.beginTransaction();
            IEREntity entity = getEntity(schema.getEntities(), "Entity2");
            IERAttribute attribute = getERAttribute(entity, "e1_Attribute2");
            IERRelationship relationship = attribute.getReferencedRelationship();
            relationship.setPhysicalName("");
			TransactionManager.endTransaction();
			assertEquals("", relationship.getPhysicalName());
		} catch (InvalidEditingException e) {
			TransactionManager.abortTransaction();
			fail();
		}
    }

    public void testSetNullPhysicalName() {
        try {
        	TransactionManager.beginTransaction();
            IEREntity entity = getEntity(schema.getEntities(), "Entity2");
            IERAttribute attribute = getERAttribute(entity, "e1_Attribute2");
            IERRelationship relationship = attribute.getReferencedRelationship();
            relationship.setPhysicalName(null);
			TransactionManager.endTransaction();
			fail();
		} catch (InvalidEditingException e) {
			TransactionManager.abortTransaction();
			assertEquals(e.getKey(), InvalidEditingException.PARAMETER_ERROR_KEY);
		}
    }

    public void testSetVerbPhraseParent() {
        try {
        	TransactionManager.beginTransaction();
            IEREntity entity = getEntity(schema.getEntities(), "Entity2");
            IERAttribute attribute = getERAttribute(entity, "e1_Attribute2");
            IERRelationship relationship = attribute.getReferencedRelationship();
            relationship.setVerbPhraseParent("verbParent");
			TransactionManager.endTransaction();
			assertEquals(relationship.getVerbPhraseParent(), "verbParent");
		} catch (InvalidEditingException e) {
			TransactionManager.abortTransaction();
			fail();
		}
    }

    public void testSetNullVerbPhraseParent() {
        try {
        	TransactionManager.beginTransaction();
            IEREntity entity = getEntity(schema.getEntities(), "Entity2");
            IERAttribute attribute = getERAttribute(entity, "e1_Attribute2");
            IERRelationship relationship = attribute.getReferencedRelationship();
            relationship.setVerbPhraseParent(null);
			TransactionManager.endTransaction();
			fail();
		} catch (InvalidEditingException e) {
			TransactionManager.abortTransaction();
			assertEquals(e.getKey(), InvalidEditingException.PARAMETER_ERROR_KEY);
		}
    }

    public void testSetVerbPhraseChild() {
        try {
        	TransactionManager.beginTransaction();
            IEREntity entity = getEntity(schema.getEntities(), "Entity2");
            IERAttribute attribute = getERAttribute(entity, "e1_Attribute2");
            IERRelationship relationship = attribute.getReferencedRelationship();
            relationship.setVerbPhraseChild("verbChild");
			assertEquals(relationship.getVerbPhraseChild(), "verbChild");
			TransactionManager.endTransaction();
		} catch (InvalidEditingException e) {
			TransactionManager.abortTransaction();
			e.printStackTrace();
		}
    }

    public void testSetNullVerbPhraseChild() {
        try {
        	TransactionManager.beginTransaction();
            IEREntity entity = getEntity(schema.getEntities(), "Entity2");
            IERAttribute attribute = getERAttribute(entity, "e1_Attribute2");
            IERRelationship relationship = attribute.getReferencedRelationship();
            relationship.setVerbPhraseChild(null);
			TransactionManager.endTransaction();
			fail();
		} catch (InvalidEditingException e) {
			TransactionManager.abortTransaction();
			assertEquals(e.getKey(), InvalidEditingException.PARAMETER_ERROR_KEY);
		}
    }

    public void testSetParentRequiredTrueInIdentifyRelationship() {
        try {
        	TransactionManager.beginTransaction();
            IEREntity entity = getEntity(schema.getEntities(), "Entity1");
            IERAttribute attribute = getERAttribute(entity, "e1_Attribute2");
            IERRelationship identifyRelationship = attribute.getReferencedRelationship();
            identifyRelationship.setParentRequired(true);
            assertEquals(true, identifyRelationship.isParentRequired());
			TransactionManager.endTransaction();
		} catch (InvalidEditingException e) {
			TransactionManager.abortTransaction();
			e.printStackTrace();
		}
    }

    public void testSetParentRequiredFalseInIdentifyRelationship() {
        try {
        	TransactionManager.beginTransaction();
            IEREntity entity = getEntity(schema.getEntities(), "Entity1");
            IERAttribute attribute = getERAttribute(entity, "e1_Attribute2");
            IERRelationship identifyRelationship = attribute.getReferencedRelationship();
            identifyRelationship.setParentRequired(false);
            TransactionManager.endTransaction();
            fail();
        } catch (InvalidEditingException e) {
			TransactionManager.abortTransaction();
			assertEquals(e.getKey(), InvalidEditingException.PARENT_REQUIRED_ERROR_KEY);
		}
    }

    public void testSetParentRequiredTrueInNonIdentifyRelationship() {
        try {
        	TransactionManager.beginTransaction();
            IEREntity entity = getEntity(schema.getEntities(), "Entity3");
            IERAttribute attribute = getERAttribute(entity, "e3_Attribute2");
            IERRelationship nonIdentifyRelationship = attribute.getReferencedRelationship();
            nonIdentifyRelationship.setParentRequired(true);
			TransactionManager.endTransaction();
			assertEquals(true, nonIdentifyRelationship.isParentRequired());
		} catch (InvalidEditingException e) {
			TransactionManager.abortTransaction();
			fail();
		}
    }

    public void testSetParentRequiredFalseInNonIdentifyRelationship() {
        try {
        	TransactionManager.beginTransaction();
            IEREntity entity = getEntity(schema.getEntities(), "Entity3");
            IERAttribute attribute = getERAttribute(entity, "e3_Attribute2");
            IERRelationship nonIdentifyRelationship = attribute.getReferencedRelationship();
            nonIdentifyRelationship.setParentRequired(false);
			TransactionManager.endTransaction();
			assertEquals(false, nonIdentifyRelationship.isParentRequired());
		} catch (InvalidEditingException e) {
			TransactionManager.abortTransaction();
			fail();
		}
    }

    public void testSetParentRequiredTrueInMultToMultRelationship() {
        try {
        	TransactionManager.beginTransaction();
            IEREntity entity = getEntity(schema.getEntities(), "Entity8");
            IERRelationship multToMultRelationship = entity.getChildrenRelationships()[0];
            multToMultRelationship.setParentRequired(true);
			TransactionManager.endTransaction();
			assertEquals(true, multToMultRelationship.isParentRequired());
		} catch (InvalidEditingException e) {
			TransactionManager.abortTransaction();
			fail();
		}
    }

    public void testSetParentRequiredFalseInMultToMultRelationship() {
        try {
        	TransactionManager.beginTransaction();
            IEREntity entity = getEntity(schema.getEntities(), "Entity8");
            IERRelationship multToMultRelationship = entity.getChildrenRelationships()[0];
            multToMultRelationship.setParentRequired(false);
			TransactionManager.endTransaction();
			assertEquals(false, multToMultRelationship.isParentRequired());
		} catch (InvalidEditingException e) {
			TransactionManager.abortTransaction();
			fail();
		}
    }

    public void testIdentifyRelationshipSetForeignKeyWithNull() {
        try {
        	TransactionManager.beginTransaction();
            IEREntity entity18 = getEntity(schema.getEntities(), "Entity18");
            IERRelationship identifyRelationship = entity18.getChildrenRelationships()[0];
            IERAttribute parent = 
            	(IERAttribute)getElement(entity18.getPrimaryKeys(), "Attribute0");
            identifyRelationship.setForeignKey(parent, null);
            TransactionManager.endTransaction();
            fail();
		} catch (InvalidEditingException e) {
			TransactionManager.abortTransaction();
			assertEquals(e.getKey(), InvalidEditingException.PARAMETER_ERROR_KEY);
		}
    }
    
    public void testIdentifyRelationshipSetForeignKey() {
        try {
        	TransactionManager.beginTransaction();
            IEREntity entity18 = getEntity(schema.getEntities(), "Entity18");
            IEREntity entity19 = getEntity(schema.getEntities(), "Entity19");
            IERRelationship identifyRelationship = entity18.getChildrenRelationships()[0];
            IERAttribute parent = 
            	(IERAttribute)getElement(entity18.getPrimaryKeys(), "Attribute0");
            IERAttribute child = 
            	(IERAttribute)getElement(entity19.getPrimaryKeys(), "Attribute1");
            identifyRelationship.setForeignKey(parent, child);
            TransactionManager.endTransaction();
		} catch (InvalidEditingException e) {
			TransactionManager.abortTransaction();
			fail();
		}
    }

    public void testIdentifyRelationshipSetIllegalForeignKey1() {
    	try {
        	TransactionManager.beginTransaction();
            IEREntity entity18 = getEntity(schema.getEntities(), "Entity18");
            IEREntity entity19 = getEntity(schema.getEntities(), "Entity19");
            IERRelationship identifyRelationship = entity18.getChildrenRelationships()[0];
            IERAttribute parent = 
            	(IERAttribute)getElement(entity18.getPrimaryKeys(), "Attribute0");
            IERAttribute child = 
            	(IERAttribute)getElement(entity19.getNonPrimaryKeys(), "Attribute2");
            identifyRelationship.setForeignKey(parent, child);
            TransactionManager.endTransaction();
            fail();
		} catch (InvalidEditingException e) {
			TransactionManager.abortTransaction();
			assertEquals(e.getKey(), InvalidEditingException.IERRElATIONSHIP_SETFORIGENKEY_FAIL_KEY);
		}
    }
    
    public void testIdentifyRelationshipSetIllegalForeignKey2() {
    	try {
        	TransactionManager.beginTransaction();
            IEREntity entity18 = getEntity(schema.getEntities(), "Entity18");
            IEREntity entity19 = getEntity(schema.getEntities(), "Entity19");
            IERRelationship identifyRelationship = entity18.getChildrenRelationships()[0];
            IERAttribute parent = 
            	(IERAttribute)getElement(entity18.getPrimaryKeys(), "Attribute0");
            IERAttribute child = 
            	(IERAttribute)getElement(entity19.getPrimaryKeys(), "Attribute3");
            identifyRelationship.setForeignKey(parent, child);
            TransactionManager.endTransaction();
            fail();
		} catch (InvalidEditingException e) {
			TransactionManager.abortTransaction();
			assertEquals(e.getKey(), InvalidEditingException.IERRElATIONSHIP_SETFORIGENKEY_FAIL_KEY);
		}
    }
    
    public void testNonIdentifyRelationshipSetForeignKeyWithNull() {
        try {
        	TransactionManager.beginTransaction();
            IEREntity entity21 = getEntity(schema.getEntities(), "Entity21");
            IERRelationship identifyRelationship = entity21.getChildrenRelationships()[0];
            IERAttribute parent = 
            	(IERAttribute)getElement(entity21.getPrimaryKeys(), "Attribute0");
            identifyRelationship.setForeignKey(parent, null);
            TransactionManager.endTransaction();
            fail();
		} catch (InvalidEditingException e) {
			TransactionManager.abortTransaction();
			assertEquals(e.getKey(), InvalidEditingException.PARAMETER_ERROR_KEY);
		}
    }
    
    public void testNonIdentifyRelationshipSetForeignKey1() {
        try {
        	TransactionManager.beginTransaction();
            IEREntity entity20 = getEntity(schema.getEntities(), "Entity20");
            IEREntity entity22 = getEntity(schema.getEntities(), "Entity22");
            IERRelationship identifyRelationship = entity20.getChildrenRelationships()[1];
            IERAttribute parent = 
            	(IERAttribute)getElement(entity20.getPrimaryKeys(), "Attribute0");
            IERAttribute child = 
            	(IERAttribute)getElement(entity22.getNonPrimaryKeys(), "Attribute1");
            identifyRelationship.setForeignKey(parent, child);
            TransactionManager.endTransaction();
		} catch (InvalidEditingException e) {
			TransactionManager.abortTransaction();
			fail();
		}
    }

    public void testNonIdentifyRelationshipSetForeignKey2() {
    	try {
        	TransactionManager.beginTransaction();
            IEREntity entity20 = getEntity(schema.getEntities(), "Entity20");
            IEREntity entity22 = getEntity(schema.getEntities(), "Entity22");
            IERRelationship identifyRelationship = entity20.getChildrenRelationships()[1];
            IERAttribute parent = 
            	(IERAttribute)getElement(entity20.getPrimaryKeys(), "Attribute0");
            IERAttribute child = 
            	(IERAttribute)getElement(entity22.getPrimaryKeys(), "Attribute2");
            identifyRelationship.setForeignKey(parent, child);
            TransactionManager.endTransaction();
		} catch (InvalidEditingException e) {
			TransactionManager.abortTransaction();
			fail();
		}
    }
    
    public void testNonIdentifyRelationshipSetIllegalForeignKey() {
    	try {
        	TransactionManager.beginTransaction();
            IEREntity entity20 = getEntity(schema.getEntities(), "Entity20");
            IEREntity entity22 = getEntity(schema.getEntities(), "Entity22");
            IERRelationship identifyRelationship = entity20.getChildrenRelationships()[1];
            IERAttribute parent = 
            	(IERAttribute)getElement(entity20.getPrimaryKeys(), "Attribute0");
            IERAttribute child = 
            	(IERAttribute)getElement(entity22.getNonPrimaryKeys(), "Attribute3");
            identifyRelationship.setForeignKey(parent, child);
            TransactionManager.endTransaction();
            fail();
		} catch (InvalidEditingException e) {
			TransactionManager.abortTransaction();
			assertEquals(e.getKey(), InvalidEditingException.IERRElATIONSHIP_SETFORIGENKEY_FAIL_KEY);
		}
    }
}

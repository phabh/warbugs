package com.change_vision.jude.api.test.model;

import junit.framework.Test;

import com.change_vision.jude.api.inf.model.IERDomain;
import com.change_vision.jude.api.inf.model.IERModel;
import com.change_vision.jude.api.inf.model.IERSchema;
import com.change_vision.jude.api.inf.model.INamedElement;

public class IERDomainTest extends ITestCase {
    private IERSchema schema;

    public static Test suite() {
        return suite("testModel/judeAPITest/ERAPITest.jude", IERDomainTest.class);
    }
    
    protected void setUp() {
        IERModel erModel = (IERModel)getElement(project.getOwnedElements(), "ER_Model");
        schema = erModel.getSchemata()[0];
    }

    public void testGetLogicalName() {
        IERDomain domain = getDomain(schema.getDomains(), "Domain0");
        assertEquals("Domain0", domain.getLogicalName());
    }

    public void testGetPhysicalName() {
        IERDomain domain = getDomain(schema.getDomains(), "Domain0");
        assertEquals("p_Domain0", domain.getPhysicalName());
    }
    
    public void testGetChildren() {
        IERDomain domain = getDomain(schema.getDomains(), "Domain0");
        IERDomain[] subDomains = domain.getChildren();
        assertTrue(contains(subDomains, "Domain2"));
        assertTrue(contains(subDomains, "Domain3"));
    }

    public void testGetDatatypeName() {
        IERDomain domain = getDomain(schema.getDomains(), "Domain0");
        assertEquals("CHAR", domain.getDatatypeName());
    }

    public void testGetLengthPrecision() {
        IERDomain domain = getDomain(schema.getDomains(), "Domain1");
        assertEquals("10,3", domain.getLengthPrecision());
    }
    
    public void testGetDefaultValue() {
        IERDomain domain = getDomain(schema.getDomains(), "Domain0");
        assertEquals("a", domain.getDefaultValue());
    }

    public void testIsNotNull_true() {
        IERDomain domain = getDomain(schema.getDomains(), "Domain0");
        assertTrue(domain.isNotNull());
    }

    public void testIsNotNull_false() {
        IERDomain domain = getDomain(schema.getDomains(), "Domain1");
        assertFalse(domain.isNotNull());
    }

//    public void testGetTypeInv() {
//        IERDomain domain = (IERDomain)getElement(domainModel.getOwnedElements(), "Domain0");
//        IERAttribute[] typeInv = domain.getTypeInv();
//        assertTrue(contains(typeInv, "Attribute2"));
//        assertTrue(contains(typeInv, "e1_Attribute2"));
//    }
    
    private boolean contains(Object[] array, String targetName){       
        for(int i = 0; i < array.length; i++){
            INamedElement element = (INamedElement) array[i];
            if(targetName.equals(element.getName())){
                return true;
            }
        }
        return false;
    }
    
    private IERDomain getDomain(IERDomain[] domains, String name){
        for(int i = 0; i < domains.length; i++) {
            if(name.equals(((IERDomain)domains[i]).getName())){
                return (IERDomain)domains[i];
            }
        }
        return null;
    }
}

package com.change_vision.jude.api.test.model;

import com.change_vision.jude.api.inf.model.IAssociation;
import com.change_vision.jude.api.inf.model.IAssociationClass;
import com.change_vision.jude.api.inf.model.IAttribute;
import com.change_vision.jude.api.inf.model.IClass;
import com.change_vision.jude.api.inf.model.IElement;

import junit.framework.Test;


public class IAssociationClassTest extends ITestCase {

    public static Test suite() {
        return suite("testModel/judeAPITest/IAssociationClassTest.jude", IAssociationClassTest.class);
    }

	public void testGetMemeberEnds() {
        IClass cls = (IClass)getElement(project.getOwnedElements(), "Class0");
        IAssociation association = cls.getAttributes()[0].getAssociation();
        assertTrue(association instanceof IAssociationClass);

        IClass aCls = (IClass)getElement(project.getOwnedElements(), "AssociationClass0");
        assertTrue(aCls instanceof IAssociationClass);
        assertEquals(aCls, association);
        
        IAttribute[] attr = ((IAssociation) association).getMemeberEnds();
        assertEquals(2, attr.length);
        assertEquals("class0", attr[0].getName());
        assertEquals("class1", attr[1].getName());
        
        int numOfAssociationClass = 0;
        for (int i = 0; i < project.getOwnedElements().length; i++) {
			IElement element = project.getOwnedElements()[i];
			if (!(element instanceof IAssociationClass))
				continue;
			checkEmployment((IAssociationClass)element);
			numOfAssociationClass++;
		}
        assertNotSame(numOfAssociationClass, 0);
	}
 	
    private static void checkEmployment(IAssociationClass employment) {
		System.out.println(employment.getMemeberEnds().length);
		for (int i = 0; i < employment.getMemeberEnds().length; i++) {
			IAttribute attr = employment.getMemeberEnds()[i];
			System.out.println(attr.getName());
		}
	}
	
	public void testGetAttributesAsAClass() {
        IClass cls = (IClass)getElement(project.getOwnedElements(), "Class0");
        IAssociation association = cls.getAttributes()[0].getAssociation();
        assertTrue(association instanceof IAssociationClass);

        IClass aCls = (IClass)getElement(project.getOwnedElements(), "AssociationClass0");
        assertTrue(aCls instanceof IAssociationClass);
        assertEquals(aCls, association);
        
        IAttribute[] attr = ((IClass) aCls).getAttributes();
        assertEquals(2, attr.length);
        assertEquals("attribute0", attr[0].getName());
        assertEquals("attribute1", attr[1].getName());
	}
}

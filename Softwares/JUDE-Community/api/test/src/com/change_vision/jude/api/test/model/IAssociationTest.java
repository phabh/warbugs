package com.change_vision.jude.api.test.model;

import com.change_vision.jude.api.inf.model.IAssociation;
import com.change_vision.jude.api.inf.model.IAttribute;
import com.change_vision.jude.api.inf.model.IClass;
import junit.framework.Test;

public class IAssociationTest extends ITestCase {

    public static Test suite() {
        return suite("testModel/judeAPITest/IAttributeTest.jude", IAssociationTest.class);
    }

	public void testGetMemeberEnds() {
        IClass cls = (IClass)getElement(project.getOwnedElements(), "Class4");
        IAssociation association = cls.getAttributes()[0].getAssociation();
        IAttribute[] attr = association.getMemeberEnds();
        
        assertEquals(2, attr.length);
        assertEquals("class4", attr[0].getName());
        assertEquals("class5", attr[1].getName());
	}
}

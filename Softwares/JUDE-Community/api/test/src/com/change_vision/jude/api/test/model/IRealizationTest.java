package com.change_vision.jude.api.test.model;

import com.change_vision.jude.api.inf.model.IClass;
import com.change_vision.jude.api.inf.model.IRealization;
import junit.framework.Test;

public class IRealizationTest extends ITestCase {

    public static Test suite() {
        return suite("testModel/judeAPITest/IClassTest.jude", IRealizationTest.class);
    }

	public void testGetClient() {
        IClass cls = (IClass)getElement(project.getOwnedElements(), "Interface1");
        IRealization[] realizations = cls.getSupplierRealizations();  // I1-C8, I1-C9

        IClass cls8 = (IClass)getElement(project.getOwnedElements(), "Class8");
        IClass cls9 = (IClass)getElement(project.getOwnedElements(), "Class9");

        assertEquals(cls8, realizations[0].getClient());
        assertEquals(cls9, realizations[1].getClient());
	}

	public void testGetSupplier() {
        IClass cls = (IClass)getElement(project.getOwnedElements(), "Interface1");
        IRealization[] realizations = cls.getSupplierRealizations();  // I1-C8, I1-C9

        assertEquals(cls, realizations[0].getSupplier());
        assertEquals(cls, realizations[1].getSupplier());
	}

}

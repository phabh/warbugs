/*
* Created on 2008/04/24
*/
package com.change_vision.jude.api.test.model;

import junit.framework.Test;

import com.change_vision.jude.api.inf.model.IClass;
import com.change_vision.jude.api.inf.model.IUsage;

/**
 * @author Harry
 */
public class IUsageTest extends ITestCase {
    public static Test suite() {
        return suite("testModel/judeAPITest/IClassTest.jude", IUsageTest.class);
    }

	public void testGetClient() {
        IClass cls = (IClass)getElement(project.getOwnedElements(), "Interface2");
        IUsage[] usages = cls.getSupplierUsages();  // "Usage"

        IClass cls10 = (IClass)getElement(project.getOwnedElements(), "Class10");

        assertEquals(cls10, usages[0].getClient());
	}

	public void testGetSupplier() {
        IClass cls = (IClass)getElement(project.getOwnedElements(), "Interface2");
        IUsage[] usages = cls.getSupplierUsages();  // "Usage"

        assertEquals(cls, usages[0].getSupplier());
	}
}

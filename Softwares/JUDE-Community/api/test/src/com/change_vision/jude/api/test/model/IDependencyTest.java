package com.change_vision.jude.api.test.model;

import com.change_vision.jude.api.inf.model.IClass;
import com.change_vision.jude.api.inf.model.IDependency;
import junit.framework.Test;

public class IDependencyTest extends ITestCase {

    public static Test suite() {
        return suite("testModel/judeAPITest/IElementTest.jude", IDependencyTest.class);
    }

    public void testGetSupplier() {
        IClass cls1 = (IClass)getElement(project.getOwnedElements(), "Class1");
        IDependency[] dependencies = cls1.getSupplierDependencies(); // dep2-1, dep3-1

        assertEquals(cls1, dependencies[0].getSupplier());
        assertEquals(cls1, dependencies[1].getSupplier());
    }

    public void testGetClient() {
        IClass cls1 = (IClass)getElement(project.getOwnedElements(), "Class1");
        IDependency[] dependencies = cls1.getSupplierDependencies(); // dep2-1, dep3-1

        IClass cls2 = (IClass)getElement(project.getOwnedElements(), "Class2");
        IClass cls3 = (IClass)getElement(project.getOwnedElements(), "Class3");

        assertEquals(cls2, dependencies[0].getClient());
        assertEquals(cls3, dependencies[1].getClient());
    }
}

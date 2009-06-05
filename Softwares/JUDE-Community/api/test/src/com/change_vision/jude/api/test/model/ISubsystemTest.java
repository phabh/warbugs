package com.change_vision.jude.api.test.model;

import junit.framework.Test;
import com.change_vision.jude.api.inf.model.INamedElement;
import com.change_vision.jude.api.inf.model.IPackage;

public class ISubsystemTest extends IPackageTest {
    
    public static Test suite() {
        return suite("testModel/judeAPITest/ISubsystemTest.jude", ISubsystemTest.class);
    }

    protected INamedElement[] getOwnerElements() {
        IPackage testPkg = (IPackage)getElement(project.getOwnedElements(), "Subsystem");
        return testPkg.getOwnedElements();
    }
}

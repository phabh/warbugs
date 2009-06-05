package com.change_vision.jude.api.test.model;

import junit.framework.Test;
import com.change_vision.jude.api.inf.model.IUseCase;

public class IUseCaseTest extends ITestCase {

    public static Test suite() {
        return suite("testModel/judeAPITest/IUseCaseTest.jude", IUseCaseTest.class);
    }

    public void testGetIncludes() {
        IUseCase usecase = (IUseCase)getElement(project.getOwnedElements(), "UseCase0");
        assertEquals(2, usecase.getIncludes().length);
        assertEquals("I1-0", usecase.getIncludes()[0].getName());
        assertEquals("I2-0", usecase.getIncludes()[1].getName());
    }

    public void testGetAdditionInvs() {
        IUseCase usecase = (IUseCase)getElement(project.getOwnedElements(), "UseCase0");
        assertEquals(2, usecase.getAdditionInvs().length);
        assertEquals("I0-3", usecase.getAdditionInvs()[0].getName());
        assertEquals("I0-4", usecase.getAdditionInvs()[1].getName());
    }

    public void testGetExtends() {
        IUseCase usecase = (IUseCase)getElement(project.getOwnedElements(), "UseCase5");
        assertEquals(2, usecase.getExtends().length);
        assertEquals("E6-5", usecase.getExtends()[0].getName());
        assertEquals("E7-5", usecase.getExtends()[1].getName());
    }

    public void testGetExtendedCaseInvs() {
        IUseCase usecase = (IUseCase)getElement(project.getOwnedElements(), "UseCase5");
        assertEquals(2, usecase.getExtendedCaseInvs().length);
        assertEquals("E5-8", usecase.getExtendedCaseInvs()[0].getName());
        assertEquals("E5-9", usecase.getExtendedCaseInvs()[1].getName());
    }

    public void testGetExtensionPoints() {
        IUseCase usecase = (IUseCase)getElement(project.getOwnedElements(), "UseCase5");
        assertEquals(2, usecase.getExtensionPoints().length);
        assertEquals("ExtensionPoint0", usecase.getExtensionPoints()[0].getName());
        assertEquals("ExtensionPoint1", usecase.getExtensionPoints()[1].getName());
    }
}

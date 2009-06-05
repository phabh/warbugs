package com.change_vision.jude.api.test.model;

import junit.framework.Test;
import com.change_vision.jude.api.inf.model.IUseCase;

public class IExtendTest extends ITestCase {
	
    public static Test suite() {
        return suite("testModel/judeAPITest/IUseCaseTest.jude", IExtendTest.class);
    }

    public void testGetExtendedCase() {
        IUseCase usecase5 = (IUseCase)getElement(project.getOwnedElements(), "UseCase5");

        IUseCase usecase6 = (IUseCase)getElement(project.getOwnedElements(), "UseCase6");
        IUseCase usecase7 = (IUseCase)getElement(project.getOwnedElements(), "UseCase7");
        assertEquals(usecase6, usecase5.getExtends()[0].getExtendedCase());
        assertEquals(usecase7, usecase5.getExtends()[1].getExtendedCase());
    }

    public void testGetExtention() {
        IUseCase usecase = (IUseCase)getElement(project.getOwnedElements(), "UseCase5");
        assertEquals(usecase, usecase.getExtends()[0].getExtension());
        assertEquals(usecase, usecase.getExtends()[1].getExtension());
    }
}

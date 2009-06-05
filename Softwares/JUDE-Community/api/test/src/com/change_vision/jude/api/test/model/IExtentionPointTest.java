package com.change_vision.jude.api.test.model;

import junit.framework.Test;
import com.change_vision.jude.api.inf.model.IUseCase;

public class IExtentionPointTest extends ITestCase {
	
    public static Test suite() {
        return suite("testModel/judeAPITest/IUseCaseTest.jude", IExtentionPointTest.class);
    }

	public void testGetOwner() {
        IUseCase usecase = (IUseCase)getElement(project.getOwnedElements(), "UseCase5");
        assertEquals(usecase, usecase.getExtensionPoints()[0].getOwner());
        assertEquals(usecase, usecase.getExtensionPoints()[1].getOwner());
	}
}

package com.change_vision.jude.api.test.model;

import com.change_vision.jude.api.inf.model.IUseCase;
import junit.framework.Test;

public class IIncludeTest extends ITestCase {

    public static Test suite() {
        return suite("testModel/judeAPITest/IUseCaseTest.jude", IIncludeTest.class);
    }

	public void testGetAddition() {
        IUseCase usecase0 = (IUseCase)getElement(project.getOwnedElements(), "UseCase0");

        IUseCase usecase1 = (IUseCase)getElement(project.getOwnedElements(), "UseCase1");
        IUseCase usecase2 = (IUseCase)getElement(project.getOwnedElements(), "UseCase2");
        assertEquals(usecase1, usecase0.getIncludes()[0].getAddition());
        assertEquals(usecase2, usecase0.getIncludes()[1].getAddition());
	}

	public void testGetIncludingCase() {
        IUseCase usecase = (IUseCase)getElement(project.getOwnedElements(), "UseCase0");
        assertEquals(usecase, usecase.getIncludes()[0].getIncludingCase());
        assertEquals(usecase, usecase.getIncludes()[1].getIncludingCase());
	}
}

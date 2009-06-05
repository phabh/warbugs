package com.change_vision.jude.api.test.model;

import junit.framework.Test;

import com.change_vision.jude.api.inf.model.IUseCaseDiagram;

public class IUseCaseDiagramTest extends ITestCase {

    public static Test suite() {
        return suite("testModel/judeAPITest/IUseCaseTest.jude", IUseCaseDiagramTest.class);
    }

    public void testGetDiagram() {
        IUseCaseDiagram dgm = (IUseCaseDiagram)getElement(project.getDiagrams(), "UseCase Diagram0");
        assertNotNull(dgm);
    }
}

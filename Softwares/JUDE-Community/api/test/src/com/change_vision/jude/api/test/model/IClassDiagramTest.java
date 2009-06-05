package com.change_vision.jude.api.test.model;

import junit.framework.Test;

import com.change_vision.jude.api.inf.model.IClassDiagram;

public class IClassDiagramTest extends ITestCase {

    public static Test suite() {
        return suite("testModel/judeAPITest/IClassTest.jude", IClassDiagramTest.class);
    }

    public void testGetDiagram() {
        IClassDiagram dgm = (IClassDiagram)getElement(project.getDiagrams(), "Class Diagram0");
        assertNotNull(dgm);
    }
    
    public void testGetERDiagram() {
        IClassDiagram dgm = (IClassDiagram)getElement(project.getDiagrams(), "ER_Diagram0");
        assertNull(dgm);
    }
}

package com.change_vision.jude.api.test.model;

import junit.framework.Test;

import com.change_vision.jude.api.inf.model.IClass;
import com.change_vision.jude.api.inf.model.IOperation;
import com.change_vision.jude.api.inf.model.ISequenceDiagram;

public class ISequenceDiagramTest extends ITestCase {

    public static Test suite() {
        return suite("testModel/judeAPITest/ISeqDgmTest.jude", ISequenceDiagramTest.class);
    }

    public void testGetDiagramsUnderOperation() {
        IClass cls = (IClass)getElement(project.getOwnedElements(), "Class0");
        IOperation op = (IOperation)getElement(cls.getOperations(), "operation0");
        ISequenceDiagram dgm = (ISequenceDiagram)getElement(op.getDiagrams(), "SeqDgm0");
        assertNotNull(dgm);
    }

    public void testGetDiagramsUnderClass() {
        IClass cls = (IClass)getElement(project.getOwnedElements(), "Class0");
        ISequenceDiagram dgm = (ISequenceDiagram)getElement(cls.getDiagrams(), "SeqDgm1");
        assertNotNull(dgm);
    }

    public void testGetDiagramsUnderProject() {
        ISequenceDiagram dgm = (ISequenceDiagram)getElement(project.getDiagrams(), "SeqDgm2");
        assertNotNull(dgm);
    }

    public void testGetInteraction() {
        ISequenceDiagram dgm = (ISequenceDiagram)getElement(project.getDiagrams(), "SeqDgm2");
        assertNotNull(dgm.getInteraction());
    }
}

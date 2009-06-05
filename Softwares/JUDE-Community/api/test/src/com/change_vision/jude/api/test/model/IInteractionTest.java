package com.change_vision.jude.api.test.model;

import junit.framework.Test;

import com.change_vision.jude.api.inf.model.IClass;
import com.change_vision.jude.api.inf.model.IInteraction;
import com.change_vision.jude.api.inf.model.IOperation;
import com.change_vision.jude.api.inf.model.ISequenceDiagram;

public class IInteractionTest extends ITestCase {

    public static Test suite() {
        return suite("testModel/judeAPITest/ISeqDgmTest.jude", IInteractionTest.class);
    }

    public void testGetArgument1() {
        IInteraction interaction = getDiagram0().getInteraction();
        assertEquals("arg", interaction.getArgument());
    }

    public void testGetArgument2() {
        IInteraction interaction = getDiagram1().getInteraction();
        assertEquals("", interaction.getArgument());
    }

    public void testGetArgument3() {
        IInteraction interaction = getDiagram2().getInteraction();
        assertEquals("", interaction.getArgument());
    }

    public void testGetLifeline0() {
        IInteraction interaction = getDiagram0().getInteraction();
        assertEquals(0, interaction.getLifelines().length);
    }

    public void testGetLifeline4() {
        IInteraction interaction = getDiagram2().getInteraction();
        assertEquals(4, interaction.getLifelines().length);
    }

    public void testGetGates0() {
        IInteraction interaction = getDiagram0().getInteraction();
        assertEquals(0, interaction.getGates().length);
    }

    public void testGetGates2() {
        IInteraction interaction = getDiagram2().getInteraction();
        assertEquals(2, interaction.getGates().length);
    }

    private ISequenceDiagram getDiagram0() {
        IClass cls = (IClass)getElement(project.getOwnedElements(), "Class0");
        IOperation op = (IOperation)getElement(cls.getOperations(), "operation0");
        return (ISequenceDiagram)getElement(op.getDiagrams(), "SeqDgm0");
    }

    private ISequenceDiagram getDiagram1() {
        IClass cls = (IClass)getElement(project.getOwnedElements(), "Class0");
        return (ISequenceDiagram)getElement(cls.getDiagrams(), "SeqDgm1");
    }

    private ISequenceDiagram getDiagram2() {
        return (ISequenceDiagram)getElement(project.getDiagrams(), "SeqDgm2");
    }
}

package com.change_vision.jude.api.test.model;

import junit.framework.Test;

import com.change_vision.jude.api.inf.model.IGate;
import com.change_vision.jude.api.inf.model.IInteraction;
import com.change_vision.jude.api.inf.model.ISequenceDiagram;

public class IGateTest extends ITestCase {

    public static Test suite() {
        return suite("testModel/judeAPITest/ISeqDgmTest.jude", IGateTest.class);
    }

    public void testGetMessage1() {
        IInteraction interaction = getDiagram().getInteraction();
        IGate gate = interaction.getGates()[0];
        assertEquals("msg0", gate.getMessage().getName());
    }

    public void testGetMessage2() {
        IInteraction interaction = getDiagram().getInteraction();
        IGate gate = interaction.getGates()[1];
        assertEquals("msg1", gate.getMessage().getName());
    }

    private ISequenceDiagram getDiagram() {
        return (ISequenceDiagram)getElement(project.getDiagrams(), "SeqDgm2");
    }
}

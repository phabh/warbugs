package com.change_vision.jude.api.test.model;

import junit.framework.Test;

import com.change_vision.jude.api.inf.model.IInteractionUse;
import com.change_vision.jude.api.inf.model.ILifeline;
import com.change_vision.jude.api.inf.model.ISequenceDiagram;

public class IInteractionUseTest extends ITestCase {

    public static Test suite() {
        return suite("testModel/judeAPITest/ISeqDgmTest.jude", IInteractionUseTest.class);
    }

    public void testGetSequenceDiagram() {
        IInteractionUse ref = getFragment("InteractionUse");
        assertEquals("SeqDgm0", ref.getSequenceDiagram().getName());
    }

    public void testGetSequenceDiagramNull() {
        IInteractionUse ref = getFragment("InteractionUse2");
        assertNull(ref.getSequenceDiagram());
    }

    public void testGetArgument() {
        IInteractionUse ref = getFragment("InteractionUse");
        assertNotNull(ref.getArgument());
        assertEquals("argarg", ref.getArgument());
    }

    public void testGetArgumentEmpty() {
        IInteractionUse ref = getFragment("InteractionUse2");
        assertNotNull(ref.getArgument());
        assertEquals("", ref.getArgument());
    }

    public void testGetGates2() {
        IInteractionUse ref = getFragment("InteractionUse");
        assertEquals(2, ref.getGates().length);
    }

    public void testGetGates0() {
        IInteractionUse ref = getFragment("InteractionUse2");
        assertEquals(0, ref.getGates().length);
    }

    public void testGetLifelines2() {
        IInteractionUse ref = getFragment("InteractionUse");
        assertEquals(2, ref.getLifelines().length);
    }

    public void testGetLifelines1() {
        IInteractionUse ref = getFragment("InteractionUse2");
        assertEquals(1, ref.getLifelines().length);
    }

    private IInteractionUse getFragment(String name) {
        ISequenceDiagram dgm = (ISequenceDiagram)getElement(project.getDiagrams(), "SeqDgm3");
        ILifeline lifeline = (ILifeline)getElement(dgm.getInteraction().getLifelines(), "lifeline2");
        return (IInteractionUse)getElement(lifeline.getFragments(), name);
    }
}

package com.change_vision.jude.api.test.model;

import junit.framework.Test;

import com.change_vision.jude.api.inf.model.ICombinedFragment;
import com.change_vision.jude.api.inf.model.IInteractionOperand;
import com.change_vision.jude.api.inf.model.ILifeline;
import com.change_vision.jude.api.inf.model.ISequenceDiagram;

public class IInteractionOperandTest extends ITestCase {

    public static Test suite() {
        return suite("testModel/judeAPITest/ISeqDgmTest.jude", IInteractionOperandTest.class);
    }

    public void testGetGuard0() {
        ICombinedFragment fragment = getFragment("CF0");
        IInteractionOperand[] operand = fragment.getInteractionOperands();
        assertEquals("Guard", operand[0].getGuard());
        assertEquals("", operand[1].getGuard());
    }

    public void testGetLifelines1() {
        ICombinedFragment fragment = getFragment("CF0");
        IInteractionOperand[] operand = fragment.getInteractionOperands();
        ILifeline[] lifelines = operand[0].getLifelines();
        assertEquals(2, lifelines.length);
        assertEquals("lifeline0", lifelines[0].getName());
        assertEquals("lifeline1", lifelines[1].getName());
    }

    public void testGetLifelines2() {
        ICombinedFragment fragment = getFragment("CF0");
        IInteractionOperand[] operand = fragment.getInteractionOperands();
        ILifeline[] lifelines = operand[0].getLifelines();
        assertEquals(2, lifelines.length);
        assertEquals("lifeline0", lifelines[0].getName());
        assertEquals("lifeline1", lifelines[1].getName());
    }

    private ICombinedFragment getFragment(String name) {
        ISequenceDiagram dgm = (ISequenceDiagram)getElement(project.getDiagrams(), "SeqDgm2");
        ILifeline lifeline = (ILifeline)getElement(dgm.getInteraction().getLifelines(), "lifeline0");
        return (ICombinedFragment)getElement(lifeline.getFragments(), name);
    }
}

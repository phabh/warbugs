package com.change_vision.jude.api.test.model;

import junit.framework.Test;

import com.change_vision.jude.api.inf.model.ICombinedFragment;
import com.change_vision.jude.api.inf.model.ILifeline;
import com.change_vision.jude.api.inf.model.INamedElement;
import com.change_vision.jude.api.inf.model.ISequenceDiagram;

public class ILifelineTest extends ITestCase {

    public static Test suite() {
        return suite("testModel/judeAPITest/ISeqDgmTest.jude", ILifelineTest.class);
    }

    public void testGetBaseOfLifeline0() {
        ILifeline lifeline = getLifeline("lifeline0");
        assertNotNull(lifeline.getBase());
    }

    public void testGetBaseOfLifeline1() {
        ILifeline lifeline = getLifeline("lifeline1");
        assertNull(lifeline.getBase());
    }

    public void testIsDestroyedOfLifeline0() {
        ILifeline lifeline = getLifeline("lifeline0");
        assertFalse(lifeline.isDestroyed());
    }

    public void testIsDestroyedOfLifeline1() {
        ILifeline lifeline = getLifeline("lifeline1");
        assertTrue(lifeline.isDestroyed());
    }

    public void testIsDestroyedOfLifeline3() {
        ILifeline lifeline = getLifeline("lifeline3");
        assertTrue(lifeline.isDestroyed());
    }

    public void testGetFragmentsOfLifeline0() {
        ILifeline lifeline = getLifeline("lifeline0");
        INamedElement[] fragments = lifeline.getFragments();
        assertEquals(5, fragments.length);
        
        assertEquals("CF0", fragments[0].getName());
        assertEquals("CF1", fragments[1].getName());
        assertEquals("aa == 0", fragments[2].getName());
        assertEquals("InteractionUse", fragments[3].getName());
        assertEquals("Destroy", fragments[4].getName());
    }

    public void testGetFragmentsOfLifeline1() {
        ILifeline lifeline = getLifeline("lifeline1");
        INamedElement[] fragments = lifeline.getFragments();
        assertEquals(2, fragments.length);

        assertEquals("CF0", fragments[0].getName());
        assertEquals("Destroy", fragments[1].getName());
    }

    public void testGetFragmentsOfLifeline2() {
        ILifeline lifeline = getLifeline("lifeline2");
        assertEquals(0, lifeline.getFragments().length);
    }

    public void testGetFragmentsOfLifeline3() {
        ILifeline lifeline = getLifeline("lifeline3");
        INamedElement[] fragments = lifeline.getFragments();
        assertEquals(2, fragments.length);

        assertEquals("msg1", fragments[0].getName());
    }
    
    public void testGetFragmentsWithOperand0OfLifeline0() {
        ILifeline lifeline = getLifeline("lifeline0");
        ICombinedFragment cf = (ICombinedFragment)lifeline.getFragments()[0];
        INamedElement[] fragments = lifeline.getFragments(cf.getInteractionOperands()[0]);
        assertEquals(4, fragments.length);

        assertEquals("msg2-1", fragments[0].getName());
        assertEquals("msg2-2", fragments[1].getName());
        assertEquals("msg3", fragments[2].getName());
        assertEquals("bb == 1", fragments[3].getName());
    }

    public void testGetFragmentsWithOperand1OfLifeline0() {
        ILifeline lifeline = getLifeline("lifeline0");
        ICombinedFragment cf = (ICombinedFragment)lifeline.getFragments()[0];
        INamedElement[] fragments = lifeline.getFragments(cf.getInteractionOperands()[1]);
        assertEquals(1, fragments.length);
        assertEquals("", fragments[0].getName());

        INamedElement[] deepestFragments = lifeline.getFragments(((ICombinedFragment) fragments[0])
                .getInteractionOperands()[0]);
        assertEquals(1, deepestFragments.length);
        assertEquals("msg4", deepestFragments[0].getName());
    }

    private ILifeline getLifeline(String name) {
        ISequenceDiagram dgm = (ISequenceDiagram)getElement(project.getDiagrams(), "SeqDgm2");
        return (ILifeline)getElement(dgm.getInteraction().getLifelines(), name);
    }
}

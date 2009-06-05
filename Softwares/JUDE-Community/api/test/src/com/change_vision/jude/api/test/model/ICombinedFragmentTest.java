package com.change_vision.jude.api.test.model;

import junit.framework.Test;

import com.change_vision.jude.api.inf.model.ICombinedFragment;
import com.change_vision.jude.api.inf.model.ILifeline;
import com.change_vision.jude.api.inf.model.INamedElement;
import com.change_vision.jude.api.inf.model.ISequenceDiagram;

public class ICombinedFragmentTest extends ITestCase {

    public static Test suite() {
        return suite("testModel/judeAPITest/ISeqDgmTest.jude", ICombinedFragmentTest.class);
    }

    public void testGetInteractionOperands_fragment0() {
        ILifeline lifeline = getLifeline("lifeline0");
        ICombinedFragment fragment = (ICombinedFragment)lifeline.getFragments()[0];
        assertEquals(2, fragment.getInteractionOperands().length);
        assertEquals("op1", fragment.getInteractionOperands()[0].getName());
        assertEquals("op2", fragment.getInteractionOperands()[1].getName());
    }

    public void testGetInteractionOperands_fragment1() {
        ILifeline lifeline = getLifeline("lifeline0");
        ICombinedFragment fragment = (ICombinedFragment)lifeline.getFragments()[1];
        assertEquals(1, fragment.getInteractionOperands().length);
        assertEquals("", fragment.getInteractionOperands()[0].getName());
    }

    public void testIsAlt() {
        ILifeline lifeline = getLifeline("lifeline0");
        INamedElement[] fragments = lifeline.getFragments();
        assertTrue(((ICombinedFragment)fragments[0]).isAlt());
        assertFalse(((ICombinedFragment)fragments[1]).isAlt());
        assertFalse(((ICombinedFragment)fragments[2]).isAlt());
        assertFalse(((ICombinedFragment)fragments[3]).isAlt());
        assertFalse(((ICombinedFragment)fragments[4]).isAlt());
        assertFalse(((ICombinedFragment)fragments[5]).isAlt());
        assertFalse(((ICombinedFragment)fragments[6]).isAlt());
        assertFalse(((ICombinedFragment)fragments[7]).isAlt());
        assertFalse(((ICombinedFragment)fragments[8]).isAlt());
        assertFalse(((ICombinedFragment)fragments[9]).isAlt());
        assertFalse(((ICombinedFragment)fragments[10]).isAlt());
        assertFalse(((ICombinedFragment)fragments[11]).isAlt());
    }

    public void testIsAssert() {
        ILifeline lifeline = getLifeline("lifeline0");
        INamedElement[] fragments = lifeline.getFragments();
        assertFalse(((ICombinedFragment)fragments[0]).isAssert());
        assertTrue(((ICombinedFragment)fragments[1]).isAssert());
        assertFalse(((ICombinedFragment)fragments[2]).isAssert());
        assertFalse(((ICombinedFragment)fragments[3]).isAssert());
        assertFalse(((ICombinedFragment)fragments[4]).isAssert());
        assertFalse(((ICombinedFragment)fragments[5]).isAssert());
        assertFalse(((ICombinedFragment)fragments[6]).isAssert());
        assertFalse(((ICombinedFragment)fragments[7]).isAssert());
        assertFalse(((ICombinedFragment)fragments[8]).isAssert());
        assertFalse(((ICombinedFragment)fragments[9]).isAssert());
        assertFalse(((ICombinedFragment)fragments[10]).isAssert());
        assertFalse(((ICombinedFragment)fragments[11]).isAssert());
    }

    public void testIsBreak() {
        ILifeline lifeline = getLifeline("lifeline0");
        INamedElement[] fragments = lifeline.getFragments();
        assertFalse(((ICombinedFragment)fragments[0]).isBreak());
        assertFalse(((ICombinedFragment)fragments[1]).isBreak());
        assertTrue(((ICombinedFragment)fragments[2]).isBreak());
        assertFalse(((ICombinedFragment)fragments[3]).isBreak());
        assertFalse(((ICombinedFragment)fragments[4]).isBreak());
        assertFalse(((ICombinedFragment)fragments[5]).isBreak());
        assertFalse(((ICombinedFragment)fragments[6]).isBreak());
        assertFalse(((ICombinedFragment)fragments[7]).isBreak());
        assertFalse(((ICombinedFragment)fragments[8]).isBreak());
        assertFalse(((ICombinedFragment)fragments[9]).isBreak());
        assertFalse(((ICombinedFragment)fragments[10]).isBreak());
        assertFalse(((ICombinedFragment)fragments[11]).isBreak());
    }

    public void testIsConsider() {
        ILifeline lifeline = getLifeline("lifeline0");
        INamedElement[] fragments = lifeline.getFragments();
        assertFalse(((ICombinedFragment)fragments[0]).isConsider());
        assertFalse(((ICombinedFragment)fragments[1]).isConsider());
        assertFalse(((ICombinedFragment)fragments[2]).isConsider());
        assertTrue(((ICombinedFragment)fragments[3]).isConsider());
        assertFalse(((ICombinedFragment)fragments[4]).isConsider());
        assertFalse(((ICombinedFragment)fragments[5]).isConsider());
        assertFalse(((ICombinedFragment)fragments[6]).isConsider());
        assertFalse(((ICombinedFragment)fragments[7]).isConsider());
        assertFalse(((ICombinedFragment)fragments[8]).isConsider());
        assertFalse(((ICombinedFragment)fragments[9]).isConsider());
        assertFalse(((ICombinedFragment)fragments[10]).isConsider());
        assertFalse(((ICombinedFragment)fragments[11]).isConsider());
    }

    public void testIsCritical() {
        ILifeline lifeline = getLifeline("lifeline0");
        INamedElement[] fragments = lifeline.getFragments();
        assertFalse(((ICombinedFragment)fragments[0]).isCritical());
        assertFalse(((ICombinedFragment)fragments[1]).isCritical());
        assertFalse(((ICombinedFragment)fragments[2]).isCritical());
        assertFalse(((ICombinedFragment)fragments[3]).isCritical());
        assertTrue(((ICombinedFragment)fragments[4]).isCritical());
        assertFalse(((ICombinedFragment)fragments[5]).isCritical());
        assertFalse(((ICombinedFragment)fragments[6]).isCritical());
        assertFalse(((ICombinedFragment)fragments[7]).isCritical());
        assertFalse(((ICombinedFragment)fragments[8]).isCritical());
        assertFalse(((ICombinedFragment)fragments[9]).isCritical());
        assertFalse(((ICombinedFragment)fragments[10]).isCritical());
        assertFalse(((ICombinedFragment)fragments[11]).isCritical());
    }

    public void testIsIgnore() {
        ILifeline lifeline = getLifeline("lifeline0");
        INamedElement[] fragments = lifeline.getFragments();
        assertFalse(((ICombinedFragment)fragments[0]).isIgnore());
        assertFalse(((ICombinedFragment)fragments[1]).isIgnore());
        assertFalse(((ICombinedFragment)fragments[2]).isIgnore());
        assertFalse(((ICombinedFragment)fragments[3]).isIgnore());
        assertFalse(((ICombinedFragment)fragments[4]).isIgnore());
        assertTrue(((ICombinedFragment)fragments[5]).isIgnore());
        assertFalse(((ICombinedFragment)fragments[6]).isIgnore());
        assertFalse(((ICombinedFragment)fragments[7]).isIgnore());
        assertFalse(((ICombinedFragment)fragments[8]).isIgnore());
        assertFalse(((ICombinedFragment)fragments[9]).isIgnore());
        assertFalse(((ICombinedFragment)fragments[10]).isIgnore());
        assertFalse(((ICombinedFragment)fragments[11]).isIgnore());
    }

    public void testIsLoop() {
        ILifeline lifeline = getLifeline("lifeline0");
        INamedElement[] fragments = lifeline.getFragments();
        assertFalse(((ICombinedFragment)fragments[0]).isLoop());
        assertFalse(((ICombinedFragment)fragments[1]).isLoop());
        assertFalse(((ICombinedFragment)fragments[2]).isLoop());
        assertFalse(((ICombinedFragment)fragments[3]).isLoop());
        assertFalse(((ICombinedFragment)fragments[4]).isLoop());
        assertFalse(((ICombinedFragment)fragments[5]).isLoop());
        assertTrue(((ICombinedFragment)fragments[6]).isLoop());
        assertFalse(((ICombinedFragment)fragments[7]).isLoop());
        assertFalse(((ICombinedFragment)fragments[8]).isLoop());
        assertFalse(((ICombinedFragment)fragments[9]).isLoop());
        assertFalse(((ICombinedFragment)fragments[10]).isLoop());
        assertFalse(((ICombinedFragment)fragments[11]).isLoop());
    }

    public void testIsNeg() {
        ILifeline lifeline = getLifeline("lifeline0");
        INamedElement[] fragments = lifeline.getFragments();
        assertFalse(((ICombinedFragment)fragments[0]).isNeg());
        assertFalse(((ICombinedFragment)fragments[1]).isNeg());
        assertFalse(((ICombinedFragment)fragments[2]).isNeg());
        assertFalse(((ICombinedFragment)fragments[3]).isNeg());
        assertFalse(((ICombinedFragment)fragments[4]).isNeg());
        assertFalse(((ICombinedFragment)fragments[5]).isNeg());
        assertFalse(((ICombinedFragment)fragments[6]).isNeg());
        assertTrue(((ICombinedFragment)fragments[7]).isNeg());
        assertFalse(((ICombinedFragment)fragments[8]).isNeg());
        assertFalse(((ICombinedFragment)fragments[9]).isNeg());
        assertFalse(((ICombinedFragment)fragments[10]).isNeg());
        assertFalse(((ICombinedFragment)fragments[11]).isNeg());
    }

    public void testIsOpt() {
        ILifeline lifeline = getLifeline("lifeline0");
        INamedElement[] fragments = lifeline.getFragments();
        assertFalse(((ICombinedFragment)fragments[0]).isOpt());
        assertFalse(((ICombinedFragment)fragments[1]).isOpt());
        assertFalse(((ICombinedFragment)fragments[2]).isOpt());
        assertFalse(((ICombinedFragment)fragments[3]).isOpt());
        assertFalse(((ICombinedFragment)fragments[4]).isOpt());
        assertFalse(((ICombinedFragment)fragments[5]).isOpt());
        assertFalse(((ICombinedFragment)fragments[6]).isOpt());
        assertFalse(((ICombinedFragment)fragments[7]).isOpt());
        assertTrue(((ICombinedFragment)fragments[8]).isOpt());
        assertFalse(((ICombinedFragment)fragments[9]).isOpt());
        assertFalse(((ICombinedFragment)fragments[10]).isOpt());
        assertFalse(((ICombinedFragment)fragments[11]).isOpt());
    }

    public void testIsPar() {
        ILifeline lifeline = getLifeline("lifeline0");
        INamedElement[] fragments = lifeline.getFragments();
        assertFalse(((ICombinedFragment)fragments[0]).isPar());
        assertFalse(((ICombinedFragment)fragments[1]).isPar());
        assertFalse(((ICombinedFragment)fragments[2]).isPar());
        assertFalse(((ICombinedFragment)fragments[3]).isPar());
        assertFalse(((ICombinedFragment)fragments[4]).isPar());
        assertFalse(((ICombinedFragment)fragments[5]).isPar());
        assertFalse(((ICombinedFragment)fragments[6]).isPar());
        assertFalse(((ICombinedFragment)fragments[7]).isPar());
        assertFalse(((ICombinedFragment)fragments[8]).isPar());
        assertTrue(((ICombinedFragment)fragments[9]).isPar());
        assertFalse(((ICombinedFragment)fragments[10]).isPar());
        assertFalse(((ICombinedFragment)fragments[11]).isPar());
    }

    public void testIsSeq() {
        ILifeline lifeline = getLifeline("lifeline0");
        INamedElement[] fragments = lifeline.getFragments();
        assertFalse(((ICombinedFragment)fragments[0]).isSeq());
        assertFalse(((ICombinedFragment)fragments[1]).isSeq());
        assertFalse(((ICombinedFragment)fragments[2]).isSeq());
        assertFalse(((ICombinedFragment)fragments[3]).isSeq());
        assertFalse(((ICombinedFragment)fragments[4]).isSeq());
        assertFalse(((ICombinedFragment)fragments[5]).isSeq());
        assertFalse(((ICombinedFragment)fragments[6]).isSeq());
        assertFalse(((ICombinedFragment)fragments[7]).isSeq());
        assertFalse(((ICombinedFragment)fragments[8]).isSeq());
        assertFalse(((ICombinedFragment)fragments[9]).isSeq());
        assertTrue(((ICombinedFragment)fragments[10]).isSeq());
        assertFalse(((ICombinedFragment)fragments[11]).isSeq());
    }

    public void testIsStrict() {
        ILifeline lifeline = getLifeline("lifeline0");
        INamedElement[] fragments = lifeline.getFragments();
        assertFalse(((ICombinedFragment)fragments[0]).isStrict());
        assertFalse(((ICombinedFragment)fragments[1]).isStrict());
        assertFalse(((ICombinedFragment)fragments[2]).isStrict());
        assertFalse(((ICombinedFragment)fragments[3]).isStrict());
        assertFalse(((ICombinedFragment)fragments[4]).isStrict());
        assertFalse(((ICombinedFragment)fragments[5]).isStrict());
        assertFalse(((ICombinedFragment)fragments[6]).isStrict());
        assertFalse(((ICombinedFragment)fragments[7]).isStrict());
        assertFalse(((ICombinedFragment)fragments[8]).isStrict());
        assertFalse(((ICombinedFragment)fragments[9]).isStrict());
        assertFalse(((ICombinedFragment)fragments[10]).isStrict());
        assertTrue(((ICombinedFragment)fragments[11]).isStrict());
    }

    private ILifeline getLifeline(String name) {
        ISequenceDiagram dgm = (ISequenceDiagram)getElement(project.getDiagrams(), "SeqDgm3");
        return (ILifeline)getElement(dgm.getInteraction().getLifelines(), name);
    }
}

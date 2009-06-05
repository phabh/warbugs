package com.change_vision.jude.api.test.model;

import junit.framework.Test;

import com.change_vision.jude.api.inf.model.ILifeline;
import com.change_vision.jude.api.inf.model.IMessage;
import com.change_vision.jude.api.inf.model.ISequenceDiagram;

public class IMessageTest extends ITestCase {

    public static Test suite() {
        return suite("testModel/judeAPITest/ISeqDgmTest.jude", IMessageTest.class);
    }

    public void testGetArgument() {
        IMessage msg = getMessage("lifeline1", "msg0");
        assertNotNull(msg.getArgument());
        assertEquals("arg", msg.getArgument());
    }

    public void testGetArgumentEmpty() {
        IMessage msg = getMessage("lifeline1", "msgAsync");
        assertNotNull(msg.getArgument());
        assertEquals("", msg.getArgument());
    }

    public void testGetGuard() {
        IMessage msg = getMessage("lifeline1", "msg0");
        assertNotNull(msg.getGuard());
        assertEquals("guard", msg.getGuard());
    }

    public void testGetGuardEmpty() {
        IMessage msg = getMessage("lifeline1", "msgAsync");
        assertNotNull(msg.getGuard());
        assertEquals("", msg.getGuard());
    }

    public void testGetReturnValue() {
        IMessage msg = getMessage("lifeline1", "msg0");
        assertNotNull(msg.getReturnValue());
        assertEquals("ret", msg.getReturnValue());
    }

    public void testGetReturnValueEmpty() {
        IMessage msg = getMessage("lifeline1", "msgAsync");
        assertNotNull(msg.getReturnValue());
        assertEquals("", msg.getReturnValue());
    }

    public void testGetIndex() {
        IMessage msg = getMessage("lifeline1", "msg0");
        assertNotNull(msg.getIndex());
        assertEquals("3", msg.getIndex());
    }

    public void testGetIndex5() {
        IMessage msg = getMessage("lifeline1", "msg2");
        assertNotNull(msg.getIndex());
        assertEquals("6", msg.getIndex());
    }

    public void testIsSynchronous() {
        IMessage aMsg = getMessage("lifeline1", "msgAsync");
        assertFalse(aMsg.isSynchronous());

        IMessage msg = getMessage("lifeline1", "msg0");
        assertTrue(msg.isSynchronous());
    }

    public void testIsAsynchronous() {
        IMessage aMsg = getMessage("lifeline1", "msgAsync");
        assertTrue(aMsg.isAsynchronous());

        IMessage msg = getMessage("lifeline1", "msg0");
        assertFalse(msg.isAsynchronous());
    }

    public void testIsReturnMessage() {
        IMessage ret = getMessage("lifeline1", "ret");
        assertTrue(ret.isReturnMessage());

        IMessage msg = getMessage("lifeline1", "msg0");
        assertFalse(msg.isReturnMessage());
    }

    public void testGetActivatorNull() {
        IMessage msg = getMessage("lifeline1", "msg0");
        assertNull(msg.getActivator());
    }

    public void testGetActivator() {
        IMessage msg = getMessage("lifeline2", "msg1-1");
        assertNotNull(msg.getActivator());
        assertEquals("msg1", msg.getActivator().getName());
    }

    public void testGetPredecessorNull() {
        IMessage msg = getMessage("lifeline1", "msg1");
        assertNull(msg.getPredecessor());
    }

    public void testGetPredecessorNull2() {
        IMessage msg = getMessage("lifeline2", "msg1-1");
        assertNull(msg.getPredecessor());
    }

    public void testGetPredecessor() {
        IMessage msg = getMessage("lifeline2", "msg1-2");
        assertNotNull(msg.getPredecessor());
        assertEquals("msg1-1", msg.getPredecessor().getName());
    }

    public void testGetSuccessorNull() {
        IMessage msg = getMessage("lifeline1", "msg1");
        assertNull(msg.getSuccessor());
    }

    public void testGetSuccessorNull2() {
        IMessage msg = getMessage("lifeline2", "msg1-2");
        assertNull(msg.getSuccessor());
    }

    public void testGetSuccessor() {
        IMessage msg = getMessage("lifeline2", "msg1-1");
        assertNotNull(msg.getSuccessor());
        assertEquals("msg1-2", msg.getSuccessor().getName());
    }

    public void testGetSource() {
        IMessage msg = getMessage("lifeline2", "msg1-1");
        assertNotNull(msg.getSource());
        assertEquals("lifeline2", msg.getSource().getName());
    }

    public void testGetTarget() {
        IMessage msg = getMessage("lifeline2", "msg1-1");
        assertNotNull(msg.getTarget());
        assertEquals("lifeline3", msg.getTarget().getName());
    }

    public void testGetSourceForGate() {
        IMessage to = getMessage("lifeline1", "msgToGate");
        assertNotNull(to.getSource());
        assertEquals("lifeline1", to.getSource().getName());

        IMessage from = getMessage("lifeline2", "msgFromGate");
        assertNull(from.getSource());
    }

    public void testGetTargetForGate() {
        IMessage to = getMessage("lifeline1", "msgToGate");
        assertNull(to.getTarget());

        IMessage from = getMessage("lifeline2", "msgFromGate");
        assertNotNull(from.getTarget());
        assertEquals("lifeline2", from.getTarget().getName());
    }

    public void testGetOperationNull() {
        IMessage msg = getMessage("lifeline1", "msg0");
        assertNull(msg.getOperation());
    }

    public void testGetOperation() {
        IMessage msg = getMessage("lifeline1", "msg2");
        assertNotNull(msg.getOperation());
        assertEquals("msg2", msg.getOperation().getName());
    }

    private IMessage getMessage(String lifelineName, String messageName) {
        ISequenceDiagram dgm = (ISequenceDiagram)getElement(project.getDiagrams(), "SeqDgm3");
        ILifeline lifeline = (ILifeline)getElement(dgm.getInteraction().getLifelines(), lifelineName);
        return (IMessage)getElement(lifeline.getFragments(), messageName);
    }
}

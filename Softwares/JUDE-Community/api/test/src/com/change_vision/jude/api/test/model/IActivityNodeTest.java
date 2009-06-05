package com.change_vision.jude.api.test.model;

import junit.framework.Test;

import com.change_vision.jude.api.inf.model.IAction;
import com.change_vision.jude.api.inf.model.IActivity;
import com.change_vision.jude.api.inf.model.IActivityDiagram;
import com.change_vision.jude.api.inf.model.IActivityNode;
import com.change_vision.jude.api.inf.model.IControlNode;
import com.change_vision.jude.api.inf.model.IDiagram;
import com.change_vision.jude.api.inf.model.IObjectNode;

public class IActivityNodeTest extends ITestCase {

    public static Test suite() {
        return suite("testModel/judeAPITest/IActivityDiagramTest.jude", IActivityNodeTest.class);
    }

    public void testAll() {
        IActivityNode[] nodes = getActivity().getActivityNodes();
        assertEquals(9, nodes.length);
        
        boolean finalStateExists = false;
        boolean initialStateExists = false;
        boolean forkExists = false;
        boolean joinExists = false;
        boolean mergeExists = false;
        
        boolean normalActionExists = false;
        boolean callingActionExists = false;
        
        boolean objectExists = false;
        boolean object2Exists = false;
        
        for (int i = 0; i < nodes.length; i++) {
            IActivityNode node = nodes[i];
            if (node instanceof IControlNode) {
                IControlNode cNode = (IControlNode)node;
                if (cNode.isFinalNode()) {
                    finalStateExists = true;
                } else if (cNode.isInitialNode()) {
                    initialStateExists = true;
                } else if (cNode.isForkNode()) {
                    forkExists = true;
                } else if (cNode.isJoinNode()) {
                    joinExists = true;
                } else if (cNode.isMergeNode()) {
                    mergeExists = true;
                }
            } else if (node instanceof IAction) {
                IAction action = (IAction)node;
                if (action.getCallingActivity() != null) {
                    assertEquals("callingAction0", action.getName());
                    assertEquals("Activity1", action.getCallingActivity().getName());
                    callingActionExists = true;
                    assertTrue(action.isCallBehaviorAction());
                } else {
                    assertEquals("action0", action.getName());
                    assertEquals(1, action.getIncomings().length);
                    assertEquals(action, action.getIncomings()[0].getTarget());
                    assertEquals(2, action.getOutgoings().length);
                    normalActionExists = true;
                    assertFalse(action.isCallBehaviorAction());
                }
            } else if (node instanceof IObjectNode) {
                IObjectNode object = (IObjectNode)node;
                if (object.getBase() != null) {
                    assertEquals("object0", object.getName());
                    assertEquals("state", object.getInState());
                    assertEquals("Class0", object.getBase().getName());
                    objectExists = true;
                } else {
                    assertEquals("object1", object.getName());
                    assertNull(object.getInState());
                    object2Exists = true;
                }
            }
        }
        
        assertTrue(finalStateExists);
        assertTrue(initialStateExists);
        assertTrue(forkExists);
        assertTrue(joinExists);
        assertTrue(mergeExists);

        assertTrue(normalActionExists);
        assertTrue(callingActionExists);

        assertTrue(objectExists);
        assertTrue(object2Exists);
    }

    private IActivity getActivity() {
        IDiagram[] dgms = project.getDiagrams();
        for (int i = 0; i < dgms.length; i++) {
            IDiagram diagram = dgms[i];
            if ("ActivityDiagram0".equals(diagram.getName())) {
                return ((IActivityDiagram)diagram).getActivity();
            }
        }
        fail("no diagram");
        return null;
    }
}

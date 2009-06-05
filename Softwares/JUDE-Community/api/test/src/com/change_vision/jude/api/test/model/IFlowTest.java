package com.change_vision.jude.api.test.model;

import junit.framework.Test;

import com.change_vision.jude.api.inf.model.IActivity;
import com.change_vision.jude.api.inf.model.IActivityDiagram;
import com.change_vision.jude.api.inf.model.IControlNode;
import com.change_vision.jude.api.inf.model.IDiagram;
import com.change_vision.jude.api.inf.model.IFlow;

public class IFlowTest extends ITestCase {

    public static Test suite() {
        return suite("testModel/judeAPITest/IActivityDiagramTest.jude", IFlowTest.class);
    }

    public void testGetName() {
        IFlow flow = getFlow();
        assertEquals("[guard] / action", flow.getName());
    }

    public void testGetSource() {
        IFlow flow = getFlow();
        assertTrue(((IControlNode)flow.getSource()).isInitialNode());
    }

    public void testGetTarget() {
        IFlow flow = getFlow();
        assertEquals("action0", flow.getTarget().getName());
    }

    public void testGetGuard() {
        IFlow flow = getFlow();
        assertEquals("guard", flow.getGuard());
    }

    public void testGetAction() {
        IFlow flow = getFlow();
        assertEquals("action", flow.getAction());
    }

    private IFlow getFlow() {
        IActivity activity = getActivity();
        IFlow[] flows = activity.getFlows();
        for (int i = 0; i < flows.length; i++) {
            IFlow flow = flows[i];
            if (flow.getName().length() > 0) {
                return flow;
            }
        }
        fail("no target flow");
        return null;
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

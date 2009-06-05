package com.change_vision.jude.api.test.model;

import junit.framework.Test;

import com.change_vision.jude.api.inf.model.IActivity;
import com.change_vision.jude.api.inf.model.IActivityDiagram;
import com.change_vision.jude.api.inf.model.IDiagram;

public class IActivityTest extends ITestCase {

    public static Test suite() {
        return suite("testModel/judeAPITest/IActivityDiagramTest.jude", IActivityTest.class);
    }

    public void testGetName() {
        IActivity activity = getActivity();
        assertEquals("Activity0", activity.getName());
    }
    
    public void testGetPartitions() {
        IActivity activity = getActivity();
        assertEquals(2, activity.getPartitions().length);
    }

    public void testGetActivityNodes() {
        IActivity activity = getActivity();
        assertEquals(9, activity.getActivityNodes().length);
    }

    public void testGetFlows() {
        IActivity activity = getActivity();
        assertEquals(3, activity.getFlows().length);
    }
    
    public void testActivityDiagram() {
        IActivity activity = getActivity();
        if (!"ActivityDiagram0".equals(activity.getActivityDiagram().getName())) {
        	fail();
        }
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

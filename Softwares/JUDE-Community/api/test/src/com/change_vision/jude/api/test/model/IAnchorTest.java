package com.change_vision.jude.api.test.model;

import junit.framework.Test;

import com.change_vision.jude.api.inf.model.IAnchor;
import com.change_vision.jude.api.inf.model.IDataFlowDiagram;
import com.change_vision.jude.api.inf.model.IDataFlowNode;
import com.change_vision.jude.api.inf.model.IDiagram;

public class IAnchorTest extends ITestCase {

	public static Test suite() {
        return suite("testModel/judeAPITest/IDataFlowDiagramTest.jude", IAnchorTest.class);
    }
	
	public void testAnchor() {
    	IDataFlowDiagram dgm = getDiagram();
    	IDataFlowNode[] dfns = dgm.getDataFlowNodes();
    	assertEquals(dfns.length, 7);
    	
    	IAnchor targetAnchor = null;
    	for (int i = 0; i < dfns.length; i++) {
			if (dfns[i] instanceof IAnchor) {
				targetAnchor = (IAnchor) dfns[i];
			}
		}	
    	assertNotNull(targetAnchor);   			
    	assertEquals(targetAnchor.getIncomings().length, 0);
    	assertEquals(targetAnchor.getOutgoings().length, 1);
    }
    
    private IDataFlowDiagram getDiagram() {
        IDiagram[] dgms = project.getDiagrams();
        for (int i = 0; i < dgms.length; i++) {
            IDiagram diagram = dgms[i];
            if ("Data Flow Diagram0".equals(diagram.getName())) {
                return (IDataFlowDiagram)diagram;
            }
        }
        fail("no diagram");
        return null;
    }
}

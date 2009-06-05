package com.change_vision.jude.api.test.model;

import junit.framework.Test;

import com.change_vision.jude.api.inf.model.IDataFlowDiagram;
import com.change_vision.jude.api.inf.model.IDataFlowNode;
import com.change_vision.jude.api.inf.model.IDiagram;
import com.change_vision.jude.api.inf.model.IExternalEntity;

public class IExternalEntityTest extends ITestCase {

	public static Test suite() {
        return suite("testModel/judeAPITest/IDataFlowDiagramTest.jude", IExternalEntityTest.class);
    }
	
	public void testExternalEntityTest() {
    	IDataFlowDiagram dgm = getDiagram();
    	IDataFlowNode[] dfns = dgm.getDataFlowNodes();
    	assertEquals(dfns.length, 7);
    	
    	IExternalEntity targetExternalEntity = null;
    	for (int i = 0; i < dfns.length; i++) {
			if (dfns[i] instanceof IExternalEntity
					&& dfns[i].getName().equals("ExternalEntity0")) {
				targetExternalEntity = (IExternalEntity) dfns[i];
			}
		}	
    	assertNotNull(targetExternalEntity);   			
    	assertEquals(targetExternalEntity.getIncomings().length, 1);
    	assertEquals(targetExternalEntity.getOutgoings().length, 0);
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

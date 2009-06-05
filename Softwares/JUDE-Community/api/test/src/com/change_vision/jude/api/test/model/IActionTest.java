/*
* Created on 2008/04/24
*/
package com.change_vision.jude.api.test.model;

import static org.junit.Assert.assertEquals;
import static org.junit.Assert.assertNotNull;
import static org.junit.Assert.fail;

import org.junit.After;
import org.junit.Before;
import org.junit.Test;

import com.change_vision.jude.api.inf.editor.TransactionManager;
import com.change_vision.jude.api.inf.exception.InvalidEditingException;
import com.change_vision.jude.api.inf.model.IActivity;
import com.change_vision.jude.api.inf.model.IActivityDiagram;
import com.change_vision.jude.api.inf.model.IActivityNode;
import com.change_vision.jude.api.inf.model.IDiagram;
import com.change_vision.jude.api.inf.model.IModel;
import com.change_vision.jude.api.inf.project.ProjectAccessor;
import com.change_vision.jude.api.inf.project.ProjectAccessorFactory;

/**
 * @author Harry
 */
public class IActionTest {

	protected static ProjectAccessor prjAccessor;
    protected static IModel project;

    @Before
	public void setup() {
		try {
            prjAccessor = ProjectAccessorFactory.getProjectAccessor();
            prjAccessor.open("testModel/judeAPITest/IActionTest.jude");
            project = prjAccessor.getProject();
        } catch (Throwable e) {
            e.printStackTrace();
        }
    }

    @After
	public void tearDown() {
		prjAccessor.close();
	}

    private IActivityDiagram getDiagram() {
        IDiagram[] dgms = project.getDiagrams();
        for (int i = 0; i < dgms.length; i++) {
            IDiagram diagram = dgms[i];
            if ("Activity Diagram0".equals(diagram.getName())) {
                return (IActivityDiagram)diagram;
            }
        }
        return null;
    }

    @Test
    public void testSetName() throws ClassNotFoundException,
    		InvalidEditingException {
    	IActivityDiagram dgm = getDiagram();
    	assertNotNull(dgm);
    	IActivity activity = dgm.getActivity();
    	assertNotNull(activity);
    	IActivityNode[] activityNodes = activity.getActivityNodes();
    	assertEquals(2, activityNodes.length);
    	assertEquals("Action0", activityNodes[0].getName());
    	assertEquals("CallBehaviorAction0", activityNodes[1].getName());
        try {
            TransactionManager.beginTransaction();
            activityNodes[0].setName("Action1");
            activityNodes[1].setName("CallBehaviorAction1");
            TransactionManager.endTransaction();
        	assertEquals("Action1", activityNodes[0].getName());
        	assertEquals("CallBehaviorAction1", activityNodes[1].getName());
        } catch (InvalidEditingException e) {
            TransactionManager.abortTransaction();
            e.printStackTrace();
            fail();
        }
    }

    @Test
    public void testSetActionMultiLineName1() throws ClassNotFoundException,
		InvalidEditingException {
		testSetActionMultiLineName("Acti\r\non1");
	}

    @Test
    public void testSetActionMultiLineName2() throws ClassNotFoundException,
    		InvalidEditingException {
		testSetActionMultiLineName("Acti\ron1");
    }

    @Test
    public void testSetActionMultiLineName3() throws ClassNotFoundException,
			InvalidEditingException {
		testSetActionMultiLineName("Acti\non1");
	}

    private void testSetActionMultiLineName(String newName) throws ClassNotFoundException,
			InvalidEditingException {
		IActivityDiagram dgm = getDiagram();
		assertNotNull(dgm);
		IActivity activity = dgm.getActivity();
		assertNotNull(activity);
		IActivityNode[] activityNodes = activity.getActivityNodes();
		assertEquals(2, activityNodes.length);
		assertEquals("Action0", activityNodes[0].getName());
		assertEquals("CallBehaviorAction0", activityNodes[1].getName());
		try {
		    TransactionManager.beginTransaction();
		    activityNodes[0].setName(newName);
		    TransactionManager.endTransaction();
		    assertEquals(newName, activityNodes[0].getName());
		} catch (InvalidEditingException e) {
			TransactionManager.abortTransaction();
			fail();
		}
    }

    @Test
    public void testSetCallBehaviorActionMultiLineName1() throws ClassNotFoundException,
			InvalidEditingException {
		testSetCallBehaviorActionMultiLineName("CallBehav\r\niorAction1");
	}

    @Test
	public void testSetCallBehaviorActionMultiLineName2() throws ClassNotFoundException,
			InvalidEditingException {
    	testSetCallBehaviorActionMultiLineName("CallBehav\riorAction1");
	}

    @Test
	public void testSetCallBehaviorActionMultiLineName3() throws ClassNotFoundException,
			InvalidEditingException {
    	testSetCallBehaviorActionMultiLineName("CallBehav\niorAction1");
	}


	private void testSetCallBehaviorActionMultiLineName(String newName) throws ClassNotFoundException,
			InvalidEditingException {
		IActivityDiagram dgm = getDiagram();
		assertNotNull(dgm);
		IActivity activity = dgm.getActivity();
		assertNotNull(activity);
		IActivityNode[] activityNodes = activity.getActivityNodes();
		assertEquals(2, activityNodes.length);
		assertEquals("Action0", activityNodes[0].getName());
		assertEquals("CallBehaviorAction0", activityNodes[1].getName());
		try {
		    TransactionManager.beginTransaction();
		    activityNodes[1].setName(newName);
		    TransactionManager.endTransaction();
		    assertEquals(newName, activityNodes[1].getName());
		} catch (InvalidEditingException e) {
			TransactionManager.abortTransaction();
			fail();
		}
	}

}

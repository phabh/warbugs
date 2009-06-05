package com.change_vision.jude.api.test.model;

import junit.framework.Test;

import com.change_vision.jude.api.inf.model.IHyperlink;
import com.change_vision.jude.api.inf.model.IMindMapDiagram;
import com.change_vision.jude.api.inf.model.INamedElement;
import com.change_vision.jude.api.inf.presentation.ITopicPresentation;

public class ITopicPresentationTest extends ITestCase {

	public static Test suite() {
        return suite("testModel/judeAPITest/ITopicPresentationTest.jude", ITopicPresentationTest.class);
    }

    public void testGetHyperlinks() {
    	INamedElement[] elements = project.getOwnedElements();
//    	IPackage pkg = (IPackage)elements[0];
//		IMindMapDiagram mm = (IMindMapDiagram) getDiagram(pkg.getDiagrams(), "root topic");
        IMindMapDiagram mm = (IMindMapDiagram) elements[0];
		ITopicPresentation rootTopic = mm.getRootTopic();
		ITopicPresentation[] topics = rootTopic.getChildren();
		ITopicPresentation topic = (ITopicPresentation) topics[0];
		if ("topic0".equals(topic.getLabel())) {
			IHyperlink[] hyperlinks = topic.getHyperlinks();
			IHyperlink hyperlink = hyperlinks[0];
			assertEquals(rootTopic.getID(), hyperlink.getName());
			assertEquals("", hyperlink.getPath());
			assertEquals("root topic comment", hyperlink.getComment());
		}
	}
}

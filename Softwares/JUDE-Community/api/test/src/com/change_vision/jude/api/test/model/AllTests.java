package com.change_vision.jude.api.test.model;

import com.change_vision.jude.api.test.editor.BasicModelEditorTest;

import junit.framework.Test;
import junit.framework.TestSuite;

public class AllTests {
    public static Test suite() {
        TestSuite suite = new TestSuite("Test for JP.co.esm.caddies.jomt.judeapi.test.model");

        //Edit API
//        suite.addTest(ERModelEditorTest.suite());
        suite.addTest(BasicModelEditorTest.suite());
        
//        suite.addTest(IElementTest.suite());
//        suite.addTest(IElementTest.suiteWithStream());
//        suite.addTest(IElementTest.suiteWithZipStream());
//
//        suite.addTest(ITaggedValueTest.suite());
//        suite.addTest(ICommentTest.suite());
//
//        suite.addTest(INamedElementTest.suite());
//        suite.addTest(ITopicPresentationTest.suite());
//        suite.addTest(IConstraintTest.suite());
//        suite.addTest(IDependencyTest.suite());
//
//        suite.addTest(IClassTest.suite());
//        suite.addTest(IAttributeTest.suite());
//        suite.addTest(IAssociationTest.suite());
//        suite.addTest(IOperationTest.suite());
//        suite.addTest(IParameterTest.suite());
//        suite.addTest(IGeneralizationTest.suite());
//        suite.addTest(IRealizationTest.suite());
//
//        suite.addTest(IAssociationClassTest.suite());
//
//        suite.addTest(IPackageTest.suite());
//        suite.addTest(ISubsystemTest.suite());
//        // no need to test IModel
//
//        suite.addTest(IUseCaseTest.suite());
//        suite.addTest(IIncludeTest.suite());
//        suite.addTest(IExtendTest.suite());
//        suite.addTest(IExtentionPointTest.suite());
//
//        suite.addTest(IDiagramTest.suite());
//
//        suite.addTest(IClassDiagramTest.suite());
//        suite.addTest(IUseCaseDiagramTest.suite());
//
//        // ActivityDiagram
//        suite.addTest(IActivityDiagramTest.suite());
//        suite.addTest(IActivityTest.suite());
//        suite.addTest(IPartitionTest.suite());
//        suite.addTest(IFlowTest.suite());
//        suite.addTest(IActivityNodeTest.suite());
//        //
//
//        // SequenceDiagram
//        suite.addTest(ISequenceDiagramTest.suite());
//        suite.addTest(IInteractionTest.suite());
//        suite.addTest(ILifelineTest.suite());
//        suite.addTest(ICombinedFragmentTest.suite());
//        suite.addTest(IInteractionOperandTest.suite());
//        suite.addTest(IGateTest.suite());
//        suite.addTest(IInteractionUseTest.suite());
//        suite.addTest(IMessageTest.suite());
//        //
//        
//        //ER Diagram
//        suite.addTest(IERModelTest.suite());
//        suite.addTest(IERDiagramTest.suite());
//        suite.addTest(IEREntityTest.suite());
//        suite.addTest(IERAttributeTest.suite());
//        suite.addTest(IERRelationshipTest.suite());
//        suite.addTest(IERSubtypeRelationshipTest.suite());
//        suite.addTest(IERDomainTest.suite());
//        suite.addTest(IERDatatypeTest.suite());
//        
//        //DFD
//        suite.addTest(IDataFlowDiagramTest.suite());
//        suite.addTest(IProcessBoxTest.suite());
//        suite.addTest(IDataStoreTest.suite());
//        suite.addTest(IExternalEntityTest.suite());
//        suite.addTest(IAnchorTest.suite());
//        suite.addTest(IDataFlowTest.suite());
        
        return suite;
    }
}

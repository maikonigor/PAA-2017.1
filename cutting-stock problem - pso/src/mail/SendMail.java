package mail;

import java.util.*;
import java.io.*;
import javax.mail.*;
import javax.mail.internet.*;
import javax.activation.*;

public class SendMail{

    public static void main(String[] args){
  if (args.length != 5){
      System.out.println("usage: java sendfile <to> <from> <smtp> <file>");
      System.exit(1);
  }

  String to = args[0];
  String from = args[1];
  String host = args[2];
  String filename = args[3];
  String msgText1 = "Enviando arquivo.\n";
  String subject = "Enviando arquivo";
  
  // cria algumas propriedades e obtem uma sessao padrao
  Properties props = System.getProperties();
  props.put("mail.smtp.host", host);
  
  Session session = Session.getInstance(props, null);

  try{
      // cria a mensagem
      MimeMessage msg = new MimeMessage(session);
      msg.setFrom(new InternetAddress(from));
      InternetAddress[] address = {new InternetAddress(to)};
      msg.setRecipients(Message.RecipientType.TO, address);
      msg.setSubject(subject);

      // cria a primeira parte da mensagem
      MimeBodyPart mbp1 = new MimeBodyPart();
      mbp1.setText(msgText1);

      // cria a segunda parte da mensage
      MimeBodyPart mbp2 = new MimeBodyPart();

            // anexa o arquivo na mensagem
         FileDataSource fds = new FileDataSource(filename);
      mbp2.setDataHandler(new DataHandler(fds));
      mbp2.setFileName(fds.getName());

      // cria a Multipart
      Multipart mp = new MimeMultipart();
      mp.addBodyPart(mbp1);
      mp.addBodyPart(mbp2);

      // adiciona a Multipart na mensagem
      msg.setContent(mp);

      // configura a data: cabecalho
      msg.setSentDate(new Date());
      
      // envia a mensagem
      Transport.send(msg);
      
  } 
  catch (MessagingException mex){
      mex.printStackTrace();
      Exception ex = null;
      if ((ex = mex.getNextException()) != null) {
    	  ex.printStackTrace();
      }
  	}
   }
}
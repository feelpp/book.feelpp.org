# Policy Page Templates

This directory contains template policy pages that can be used as starting points for your Antora documentation site.

## Available Templates

- `terms-of-use.adoc` - Terms and conditions for software/service usage
- `privacy-policy.adoc` - Privacy policy covering data collection and protection
- `cookie-policy.adoc` - Cookie usage policy for websites
- `support-policy.adoc` - Support channels and expectations

## How to Use

### 1. Copy to Your Project

Copy the relevant policy files to your Antora content directory:

```bash
# Copy to your docs/modules/ROOT/pages/ directory
cp templates/policy-pages/*.adoc /path/to/your/docs/modules/ROOT/pages/
```

### 2. Customize for Your Project

Each template contains placeholder sections marked with:

```adoc
[NOTE]
====
Replace this section with information about your organization
====
```

Update these sections with your specific information:

- Organization name and contact details
- Legal jurisdiction
- Specific services and data practices
- Actual cookie implementations
- Support contact information

### 3. Update Navigation

Add the policy pages to your navigation file (`nav.adoc`):

```adoc
* Policies & Legal
** xref:terms-of-use.adoc[Terms of Use]
** xref:privacy-policy.adoc[Privacy Policy]
** xref:cookie-policy.adoc[Cookie Policy]
** xref:support-policy.adoc[Support Policy]
```

### 4. Update Footer Links

If using the Feel++ Antora UI, the footer is already configured to link to these pages. If using a custom footer, update your footer template:

```handlebars
<div class="footer-terms-links">
  <a href="{{relativize 'your-component/terms-of-use.html'}}">Terms of Use</a>
  <a href="{{relativize 'your-component/privacy-policy.html'}}">Privacy Policy</a>
  <a href="{{relativize 'your-component/cookie-policy.html'}}">Cookie Policy</a>
  <a href="{{relativize 'your-component/support-policy.html'}}">Support Policy</a>
</div>
```

## Legal Compliance

These templates are designed to help with common legal requirements:

- **GDPR Compliance**: Privacy and cookie policies include GDPR-required elements
- **Academic Use**: Terms include provisions for research and educational use
- **Open Source**: Policies accommodate open-source development models

### Important Notes

⚠️ **Legal Disclaimer**: These are templates only. You should:

- Consult with legal counsel for your specific jurisdiction
- Customize based on your actual practices
- Review and update regularly
- Ensure accuracy for your specific use case

## Template Features

### Terms of Use
- Open source license compatibility
- Academic and research use provisions
- Contribution guidelines
- Liability limitations

### Privacy Policy
- GDPR compliance structure
- Data collection categories
- Legal basis explanations
- User rights information

### Cookie Policy
- Cookie categorization table
- Third-party service disclosure
- User control options
- Technical implementation details

### Support Policy
- Community support model
- Response time expectations
- Professional support options
- Contribution encouragement

## Maintenance

Keep these policies updated:

- Review annually or when practices change
- Update contact information as needed
- Align with software/service changes
- Monitor legal requirement changes

## Contributing

If you improve these templates, consider contributing back:

1. Fork the antora-ui repository
2. Update the templates in `src/static/templates/policy-pages/`
3. Submit a pull request with your improvements

## Questions

For questions about these templates:

- Open an issue in the antora-ui repository
- Join the Feel++ community discussions
- Consult your legal advisor for legal questions